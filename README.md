# DRAM Tester x1x4 lcd by Goripon Hardware

[日本語版 README はこちら](https://github.com/goriponsoft/Dram-Tester-x1x4-lcd/blob/main/README-ja.md)


 This is a stand-alone DRAM tester compatible with 4116/4164/41256/4532/4416/4464/44256 and equipped with an LCD.


 Although it is not a direct fork, it is created based on zeus074/dramtester and cloudree/DRAM_Tester.

 Both of the two references are under the GPL3.0 license, so this DRAM tester will also be released under the GPL3.0 license.


 This DRAM tester was created by Goripon Hardware (the hardware division of Doujin Circle Goripon Software).

 X(old Twitter): @goriponsoft


**Components:**

C1,C2,C3,C4,C8: Unpolarized capacitor 100nF (Withstand voltage 16V or more.)

C5: Polarized capacitor 470uF (Withstand voltage 16V or more.)

C6: Polarized capacitor 47uF (Withstand voltage 16V or more.)

C7: Polarized capacitor 10uF (Withstand voltage 16V or more.)

IC1: DC-DC Converter, 8-Pin PDIP "TC7660S"

J1: DC Power Connector, Jack "MJ-179PH"

JP1: Pin Header 1x3 and Jumper Pin

LED1: LED, D3.0mm, Yellow

LED2: LED, D3.0mm, Green or Red

R1-R13: Resistor 47 ohm, 1/4 watt, tolerance 5%

R14, R17: Resistor 10K ohm, 1/4 watt, tolerance 5%

R15: Resistor 1.5K ohm, 1/4 watt, required low tolerance

R16: Resistor 750 ohm, 1/4 watt, required low tolerance

R18: Resistor 5.1K ohm, 1/4 watt, tolerance 5%

S0-S1: 3M Zero pressure (ZIF) socket 16pin "216-3340-00-0602J"

S2: 3M Zero pressure (ZIF) socket 18pin "218-3341-00-0602J"

S3: 3M Zero pressure (ZIF) socket 20pin "220-3342-00-0602J"

SW1: 6x6 Through hole & ground terminal type tactile switch "DTS-63N-V"

SW2: Switch Slide ON None ON SPDT Top Slide Thru-Hole "SS12SDP2"

SW3: Switch Slide ON None ON DPDT Top Slide Thru-Hole "SS22SDP2"

U1: Arduino Nano

U2: MT3608 DCDC Module

U3: I2C OLED Screen 0.91in. 128x32dots

Pin header for module installation

9V-12V Center+ ACDC adapter


**Directory**

firmware:

 Firmware for Arduino Nano.


firmware/ArduinoIDE/Dram-Tester-x1x4-lcd:

 Firmware source code for Arduino IDE environment.

 You can compile and write sketches using the Arduino IDE.


firmware/PlatformIO/Dram-Tester-x1x4-lcd:

 Firmware source code for PlatformIO environment.

 You can compile using PlatformIO and write compiled binaries.


firmware/ArduinoIDE/Dram-Tester-x1x4-lcd/build:

firmware/PlatformIO/Dram-Tester-x1x4-lcd/.pio/build/Arduino_nano:

 Firmware compiled binary.

 You can write HEX files using AVR programmer.


schematic:

 Schematic data for KICAD7.


schematic/production:

 Gerber data for PCB.


**Preparation**

0. AC adapter connection.

 Connect the AC adapter (center positive, 7V to 12V) to the DC jack and turn on the main power switch.

 Although it can be operated by connecting a 5V power supply or PC to the Arduino Nano's USB connector, we recommend using an AC adapter.


1. Writing firmware to Arduino Nano.

 Connect to your PC via USB and use the Arduino IDE to write compiled sketches, or use PlatformIO or AVR writers to write HEX files.


2. Adjust the voltage of MT3608 module.

 While measuring the voltage with a multimeter, turn the semi-fixed ohmic and adjust it to 12V.

 If you do not have a tester, you can also turn on the power switch or reset it while holding down the SELECT/ENTER button to activate the setting change mode and display the voltage, but this is not recommended as the accuracy is low.

 (In order to use the voltage measurement function in the setting mode, it is necessary that the error in the resistances of R15 and R16 is small, and (if possible) write the correction value to the EEPROM.)


**How it works**

0. AC adapter connection.

 Connect the AC adapter (center positive, 7V to 12V) to the DC jack.


1. Inserting DRAM to test

 Turn off socket power switch, then insert DRAM under test into the socket.

 Insert into SOCKET0 for 4116, SOCKET1 for 4164/41256/4532, SOCKET2 for 4416/4464, and SOCKET3 for 44256.

 *Please note that if you insert a DRAM other than 4116 type into SOCKET0, it will be damaged.


2. Select the model number of the DRAM to be tested

 Turn on socket power switch, check the LCD display, and select DRAM model number by pressing SELECT/ENTER button.

 The socket into which the DRAM should be inserted will also be displayed on the LCD, so check that it is correct.


3. Start test

 Press and hold the SELECT/ENTER button to start the test.


4. Results display

 After waiting a few tens of seconds to a few minutes (depending on the amount of DRAM and test stringency settings, less if an error occurs), the results will be displayed.


5. Removing the DRAM after testing

 Turn off the socket power switch and remove the tested DRAM from the socket.

 If you want to replace it with another DRAM after testing, please turn off the socket power switch first.


**Setting change**

 By holding down the SELECT/ENTER button and turning on the main power switch, you can start up in setting change mode.

 As with normal DRAM model selection, short press the SELECT/ENTER button to select an item, long press to confirm or change settings.


4bit DRAM Test:

 Select whether to test 4bit DRAM with priority given to speed ("Speedy") or strictly ("Strict").


Power5V Voltage:

 Check the voltage of the 5V power supply and select whether to abort the test ("Check") or ignore it and continue the test ("Ignore") if the voltage is abnormal.

 In the case of USB power, the voltage of the power supply may drop and the test may not be performed correctly.


Erase EEPROM:

 You can initialize the settings by erasing the contents of the EEPROM (values for correction, etc. remain).

 When erasing is complete, you will be forced to exit the settings change mode.


View Power12V:

 Displays voltage of 12V power supply and voltage error.

 If 12V power supply voltage is not appropriate, the 4116 DRAM cannot be tested.

 Please reset when exiting.


View Button & Power5V:

 Displays button test and 5V power status.

 Please reset when exiting.


Save and Exit:

 Save the changes, exit setting change mode, and proceed to normal DRAM model number selection.

 Changes will not be saved unless you exit setting change mode.

 If you do not want to save, you can avoid saving by resetting without making a decision with this item.

