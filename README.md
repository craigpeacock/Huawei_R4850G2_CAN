# Huawei R4850G2 Rectifier / 53.5VDC 3000W Power Supply.
This is example Linux ANSI-C code to communicate with the Huawei R4850 Rectifier / Power Supply via CAN. For details on the PSU and wiring, visit:
* [Review: Huawei R4850G2 Power Supply 53.5VDC, 3kW with CAN](https://www.beyondlogic.org/review-huawei-r4850g2-power-supply-53-5vdc-3kw/)

This code can be executed on the following targets:
 * Beaglebone Black: https://www.beyondlogic.org/adding-can-to-the-beaglebone-black/
 * Raspberry PI: https://www.beyondlogic.org/adding-can-controller-area-network-to-the-raspberry-pi/
 * Linux Desktop with suitable SocketCAN interface (i.e. [Inno-maker USB-CAN](https://www.inno-maker.com/product/usb-can/), PCAN-USB from Peak Systems)

By default the Huawei rectifier communicates at 125kbps with extended 29-bit addressing. Use the following to set up your link:

```
$ sudo /sbin/ip link set can0 up type can bitrate 125000
```
To view the current statistics, run: (Where can0 is your can device)

```
$ ./r4850 can0

Huawei R4850G2 53.5VDC 3000W Rectifier Configuration Utility V1.1
http://www.beyondlogic.org

Input Voltage 237.88V @ 50.03Hz
Input Current 0.41A
Input Power 98.18W

Output Voltage 47.98V
Output Current 1.97A of 37.70A Max, 0.002Ah
Output Power 89.36W

Input Temperature 27.0 DegC
Output Temperature 27.0 DegC
Efficiency 91.0%
```

To change the preset voltage and current, use the -v & -c switches as per below.

```
Huawei R4850G2 53.5VDC 3000W Rectifier Configuration Utility V1.1
http://www.beyondlogic.org
Usage: r4850 [options] <CAN interface>
Options:
	-v <voltage>	(Set Power Supply Voltage)
	-c <current>	(Set Maximum Current)
	-s              (Save settings to non-volatile memory/off-line)
```

The -v & -c switches set the on-line settings. Append -s to save to the off-line (non-volatile) settings.

For details on on-line vs off-line settings, please see
https://www.beyondlogic.org/review-huawei-r4850g2-power-supply-53-5vdc-3kw/#modes_of_operation

## Debugging

The rectifier will send out unsolcitied messages and this is a good way to ensure your hardware is working correctly. Run candump can0 (from CAN-utils) and verify you see frames similar to below (This dump is from power-up) :

```
$ candump can0
  can0  1000107E   [8]  30 01 6C 68 84 64 2D A4
  can0  1000107E   [8]  30 01 6C 68 84 64 2D A4
  can0  1000107E   [8]  30 01 6C 68 84 64 2D A4
  can0  1001107E   [8]  30 02 6C 68 84 64 2D A4
  can0  1001107E   [8]  30 02 6C 68 84 64 2D A4
  can0  1001107E   [8]  30 02 6C 68 84 64 2D A4
  can0  1001107E   [8]  30 02 6C 68 84 64 2D A4
  can0  1001107E   [8]  30 02 6C 68 84 64 2D A4
  can0  1001107E   [8]  30 02 6C 68 84 64 2D A4
  can0  1001107E   [8]  30 02 6C 68 84 64 2D A4
  can0  1001107E   [8]  30 02 6C 68 84 64 2D A4
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  108081FE   [8]  01 13 00 01 00 00 00 00
  can0  100011FE   [8]  00 02 00 00 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  108111FE   [8]  00 03 00 00 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  108111FE   [8]  00 03 00 00 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  108111FE   [8]  00 03 00 00 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  108111FE   [8]  00 03 00 00 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  108111FE   [8]  00 03 00 00 00 00 00 00
  can0  1001117E   [8]  00 01 00 01 00 00 00 00
  can0  108111FE   [8]  00 03 00 00 00 00 00 00
```

## Protocol

The data above can be requested by sending:

```
 can0  108040FE   [8]  00 00 00 00 00 00 00 00
```

The rectifier will then return the following packets:

```
  can0  1081407F   [8]  01 0E 00 00 00 00 00 0A  
  can0  1081407F   [8]  01 70 00 00 00 01 A6 84   (Input Power)
  can0  1081407F   [8]  01 71 00 00 00 00 C8 0A   (Input Freq)
  can0  1081407F   [8]  01 72 00 00 00 00 01 C2   (Input Current)
  can0  1081407F   [8]  01 73 00 00 00 01 80 8E   (Output Power)
  can0  1081407F   [8]  01 74 00 00 00 00 03 A4   (Efficiency)
  can0  1081407F   [8]  01 75 00 00 00 00 D5 C8   (Output Voltage)
  can0  1081407F   [8]  01 76 00 00 00 00 04 6A   (Maximum Output Current)
  can0  1081407F   [8]  01 78 00 00 00 03 C0 80   (Input Voltage)
  can0  1081407F   [8]  01 7F 00 00 00 00 64 00   (Output Stage Temperature)
  can0  1081407F   [8]  01 80 00 00 00 00 70 00   (Input Stage Temperature)
  can0  1081407F   [8]  01 81 00 00 00 00 07 B2   
  can0  1081407F   [8]  01 82 00 00 00 00 07 32   (Output Current)
  can0  1081407E   [8]  01 83 00 10 00 00 00 00
```

## User Feedback on Maximum Current

This software contains a MAX_CURRENT_MULTIPLIER definition used to set (and report) the rectifier's maximum current. Some references on the Web suggest the maximum current multiplier should be set to 30 (decimal). With my unit, it would appear 20 provides a more accurate current limit when charging LiFePO4 battery packs. It is not known if this changes per unit, i.e. requires calibration. I welcome feedback on maximum current accuracy via GitHub issues.

## Acknowledgements

This work is based on esp32 code developed by BotoX

https://github.com/BotoX/huawei-r48xx-esp32

https://github.com/BotoX/r4830g2-tiva








