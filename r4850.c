#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#define R48xx_DATA_INPUT_POWER	0x70
#define R48xx_DATA_INPUT_FREQ		0x71
#define R48xx_DATA_INPUT_CURRENT	0x72
#define R48xx_DATA_OUTPUT_POWER	0x73
#define R48xx_DATA_EFFICIENCY		0x74
#define R48xx_DATA_OUTPUT_VOLTAGE	0x75
#define R48xx_DATA_OUTPUT_CURRENT_MAX	0x76
#define R48xx_DATA_INPUT_VOLTAGE	0x78
#define R48xx_DATA_OUTPUT_TEMPERATURE	0x7F

int r4850_data(uint8_t *frame)
{

	uint32_t value = __builtin_bswap32(*(uint32_t *)&frame[4]);
	//printf("Get Data: %02X, Value %04X\r\n",frame[1], value);

	switch (frame[1]) {
		case R48xx_DATA_INPUT_POWER:
			printf("Input Power %.02fW\r\n", value / 1024.0);
			break;
		case R48xx_DATA_INPUT_FREQ:
			printf("Input Frequency %.02fHz\r\n", value / 1024.0);
			break;

		case R48xx_DATA_INPUT_CURRENT:
			printf("Input Current %.02fA\r\n", value / 1024.0);
			break;

		case R48xx_DATA_OUTPUT_POWER:
			printf("Output Power %.02fW\r\n", value / 1024.0);
			break;

		case R48xx_DATA_EFFICIENCY:
			printf("Efficiency %.02f%%\r\n", value / 1024.0);
			break;

		case R48xx_DATA_OUTPUT_VOLTAGE:
			printf("Output Voltage %.02fV\r\n", value / 1024.0);
			break;

		case R48xx_DATA_OUTPUT_CURRENT_MAX:
			printf("Output Current (Max) %.02fA\r\n", value / 30.0);
			break;

		case R48xx_DATA_INPUT_VOLTAGE:
			printf("Input Voltage %.02fV\r\n", value / 1024.0);
			break;

		case R48xx_DATA_OUTPUT_TEMPERATURE:
			printf("Temperature %.02fDegC\r\n", value / 1024.0);
			break;

		default:
			break;

	}
}

int main(int argc, char **argv)
{
	int s, i;
	int frame_number;
	int nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	printf("R4850G2 CAN Interface Example\r\n");

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

	strcpy(ifr.ifr_name, "can0" );
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return 1;
	}

	do {

		nbytes = read(s, &frame, sizeof(struct can_frame));

		if (nbytes < 0) {
			perror("Read");
			return 1;
		}
#if debug
		printf("0x%03X [%d] ",(frame.can_id & 0x1FFFFFFF), frame.can_dlc);
		for (i = 0; i < frame.can_dlc; i++)
			printf("%02X ",frame.data[i]);
		printf("\r\n");
#endif

		switch (frame.can_id & 0x1FFFFFFF){

			case 0x1081407F:
				r4850_data((uint8_t *)&frame.data);
				break;
		}

	} while(1);

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
