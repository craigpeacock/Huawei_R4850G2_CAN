# Huawei R4850G2 Rectifier / 53.5VDC 3000W Power Supply.
This is example Linux ANSI-C code to communicate with the Huawei R4850 Rectifier / Power Supply via CAN.

This code can be executed on the following targets:
 * Beaglebone Black: https://www.beyondlogic.org/adding-can-to-the-beaglebone-black/
 * Raspberry PI: https://www.beyondlogic.org/adding-can-controller-area-network-to-the-raspberry-pi/
 * Linux Desktop with suitable SocketCAN interface (i.e. PCAN-USB from Peak Systems)

By default the Huawei rectifier communicates at 1250kbps with extended 29-bit addressing. Use the following to set up your link:

```
$ sudo /sbin/ip link set can0 up type can bitrate 125000
```

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

Now run the ./r4850 example code:

```
$ ./r4850
R4850G2 CAN Interface Example
Unknown parameter 0x0E, 0x000A
Input Power 104.32W
Input Frequency 50.03Hz
Input Current 0.43A
Output Power 94.95W
Efficiency 0.91%
Output Voltage 53.39V
Output Current (Max) 37.70A
Input Voltage 240.12V
Output Temperature 22.00DegC
Input Temperature 29.00DegC
Unknown parameter 0x81, 0x07B2
Output Current 1.78A
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

## Acknowledgements

This work is based on esp32 code developed by BotoX

https://github.com/BotoX/huawei-r48xx-esp32
https://github.com/BotoX/r4830g2-tiva







