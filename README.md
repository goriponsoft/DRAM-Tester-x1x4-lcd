# DRAM Tester x1x4 lcd by Goripon Hardware
![](front.jpg)

[日本語版 README はこちら](https://github.com/goriponsoft/Dram-Tester-x1x4-lcd/blob/main/README-ja.md)

 This is a stand-alone DRAM tester compatible with 4116/4164/41256/4532/4416/4464/44256 and equipped with an LCD. Although it is not a direct fork, it is created based on [zeus074/dramtester](https://github.com/zeus074/dramtester) and [cloudree/DRAM_Tester](https://github.com/cloudree/DRAM_Tester). Thanks to the two original authors. Both of the two references are under the GPL3.0 license, so this DRAM tester will also be released under the GPL3.0 license.

 This DRAM tester was created by Goripon Hardware (the hardware division of Doujin Circle Goripon Software).

 X(old Twitter): @goriponsoft


# Components
(Check schematic/bom.xlsx as it may not match the schematic updates)
|Part Number|Parts|Quantity|
|:--|:--|--:|
|C1-C4|Unpolarized capacitor 100nF (Withstand voltage 16V or more.)|4|
|C5,C8|Polarized capacitor 470uF (Withstand voltage 16V or more.)|2|
|C6,C7|Polarized capacitor 10uF (Withstand voltage 16V or more.)|2|
|IC1|DC-DC Converter(Charge pump), 8-Pin PDIP "TJ7660"|1|
|CN1|DC Power Connector, Jack "MJ-179PH"|1|
|JP1|Pin Header 1x3 and Jumper Pin|1|
|JP2|Pin Header 1x2 and Jumper Pin|1|
|LED1|LED, D3.0mm, Yellow (Forward voltage 2.1V)|1|
|LED2|LED, D3.0mm, Green or Red (Forward voltage 2.1V)|1|
|R1-R11,R19|Resistor 47 ohm, 1/4 watt, tolerance 5%|12|
|R12,R13|Resistor 47 ohm, 1/6 watt, tolerance 5%|2|
|R14,R17|Resistor 10K ohm, 1/4 watt, tolerance 5%|2|
|R15|Resistor 1.5K ohm, 1/4 watt, required low tolerance (ex. 1%)|1|
|R16|Resistor 750 ohm, 1/4 watt, required low tolerance (ex. 1%)|1|
|R18|Resistor 5.1K ohm, 1/4 watt, tolerance 5%|1|
|S0-S1|3M Zero pressure (ZIF) socket 16pin "216-3340-00-0602J"|2|
|S2|3M Zero pressure (ZIF) socket 18pin "218-3341-00-0602J"|1|
|S3|3M Zero pressure (ZIF) socket 20pin "220-3342-00-0602J"|1|
|SW1|6x6mm Through hole & ground terminal type tactile switch "DTS-63N-V"|1|
|SW2|Switch Slide ON None ON SPDT Top Slide Thru-Hole "SS12SDP2"|1|
|SW3|Switch Slide ON None ON DPDT Top Slide Thru-Hole "SS22SDP2"|1|
|U1|Arduino Nano|1|
|U2|MT3608 DCDC Module|1|
|U3|I2C OLED Screen 0.91in. 128x32dots|1|
|-|Pin header for module installation|-|
|-|9V-12V 1A Center+ ACDC adapter|1|

# Directory
- firmware: Firmware for Arduino Nano.
- firmware/ArduinoIDE/Dram-Tester-x1x4-lcd: Firmware source code for Arduino IDE environment. You can compile and write sketches using the Arduino IDE.
- firmware/ArduinoIDE/Dram-Tester-x1x4-lcd/build: Firmware compiled binary. You can write HEX files using AVR programmer.
- firmware/PlatformIO/Dram-Tester-x1x4-lcd: Firmware source code for PlatformIO environment. You can compile using PlatformIO and write compiled binaries.
- firmware/PlatformIO/Dram-Tester-x1x4-lcd/.pio/build/Arduino_nano: Firmware compiled binary. You can write HEX files using AVR programmer.
- schematic: Schematic data for KICAD7.
- schematic/production: Gerber data for PCB ordering.

# How to assemble
Refer to the photo of the finished product on this page and solder and place the components according to the silk screen printing on the board.

For the Arduino Nano, DCDC converter board, and OLED display, first solder the headers to the components, then insert the pin headers into the board and solder them. No other special steps are required, so follow the normal assembly method for electronic circuits.

# Preparation
*For the finished products and kits we distribute, steps 1 to 6 are not necessary because the firmware is already written.

1. Connect the power supply to the board (USB connector or DC jack), turn on the main power switch, and measure the 3.3V power output of the Arduino Nano with a voltage tester and make a note of it.
2. Change "#if 0" to "#if 1" near the beginning of the setup() function in Dram-Tester-x1x4-lcd.cpp (or Dram-Tester-x1x4-lcd.ino), and replace the "3.300" part of the equation that assigns a value to the calibrationValue variable with the voltage you noted down (if you don't mind the error, you can leave it as 3.300, but the voltage check may not work correctly).
3. Connect the Arduino Nano to the PC via USB, and write the compiled sketch using the Arduino IDE, or write the HEX file using PlatformIO or an AVR writer.
4. Turn the main power switch on and off on the board, or press the reset button to start the firmware (the modified firmware will run and the voltage correction value will be written to the EEPROM).
5. Change "#if 1" in the source back to "#if 0". Note that steps 1 to 5 only need to be done the first time, and are not necessary thereafter.
6. Write the compiled sketch again using the Arduino IDE, or write the HEX file using PlatformIO or AVR writer.
7. Turn on the main power switch on the board, then turn the tri-pot resistor of the MT3608DCDC converter module while measuring the voltage with a tester to adjust it to 12V. You can also press and hold the SELECT/ENTER button while turning on or resetting the power switch to enter the setting change mode and display the voltage.
8. Set the jumper pin of JP1 (socket power LED operation). When 1-2 is shorted, the light turns on when ON, when 2-3 is shorted, the light turns on when OFF, and when the jumper pin is removed, the light turns off all the time.

# How it works
0. Connect the ACDC adapter (center positive, 9V to 12V, 1A) to the DC jack. Although it can be operated by connecting a 5V power supply or PC to the Arduino nano's USB connector, we recommend using an ACDC adapter.
1. Turn off socket power switch, then insert DRAM under test into the socket. Insert into SOCKET0 for 4116, SOCKET1 for 4164/41256/4532, SOCKET2 for 4416/4464, and SOCKET3 for 44256. *Please note that if you insert a DRAM other than 4116 type into SOCKET0, it will be damaged.
2. Turn on socket power switch, check the LCD display, and select DRAM model number by pressing SELECT/ENTER button. The socket into which the DRAM should be inserted will also be displayed on the LCD, so check that it is correct.
3. Press and hold the SELECT/ENTER button to start the test. *For safety reasons, the buttons cannot be operated while the socket power switch is off.
4. After waiting a few tens of seconds to a few minutes (depending on the amount of DRAM and test stringency settings, less if an error occurs), the results will be displayed.
5. Turn off the socket power switch and remove the tested DRAM from the socket. If you want to replace it with another DRAM after testing, please turn off the socket power switch first.

# Setting change
By holding down the SELECT/ENTER button and turning on the main power switch, you can start up in setting change mode. As with normal DRAM model selection, short press the SELECT/ENTER button to select an item, long press to confirm or change settings.

- 4bit DRAM Test: Select whether to test 4bit DRAM with priority given to speed ("Speedy") or strictly ("Strict").
- Power5V Voltage: Check the voltage of the 5V power supply and select whether to abort the test ("Check") or ignore it and continue the test ("Ignore") if the voltage is abnormal. In the case of USB power, the voltage of the power supply may drop and the test may not be performed correctly.
- Erase EEPROM: You can initialize the settings by erasing the contents of the EEPROM (values for correction, etc. remain). When erasing is complete, you will be forced to exit the settings change mode.
- View Power12V: Displays voltage of 12V power supply and voltage error. If 12V power supply voltage is not appropriate, the 4116 DRAM cannot be tested. Please reset when exiting. *Voltage cannot be displayed if the socket power is turned off.
- View Button & Power5V: Displays button test and 5V power status. Please reset when exiting.
- Save and Exit: Save the changes, exit setting change mode, and proceed to normal DRAM model number selection. Changes will not be saved unless you exit setting change mode. If you do not want to save, you can avoid saving by resetting without making a decision with this item.

