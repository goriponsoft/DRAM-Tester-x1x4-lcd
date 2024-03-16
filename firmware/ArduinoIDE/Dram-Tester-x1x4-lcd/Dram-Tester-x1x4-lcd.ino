#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <EEPROM.h>

// #define _DEBUG			// Debug Function enable
// #define _DEMO_MODE		// Demo Mode firmware
// #define _BUS_A9_ENABLE	// Adress bus bit9 (PD1) enable (Not tested.)
// #define _4M_DRAM_ENABLE // 4M(1024Kx4) DRAM support enable. (Not tested & _BUS_A9_ENABLE required.)

#define VERSION_STRING "0.0.0"
#define NAME_STRING "DRAM-Tester"
#define SUBNAME_STRING "x1/x4"

#define MIN_DRAMCONF 0
#define DRAMCONF_16X1 0
#define DRAMCONF_64X1 1
#define DRAMCONF_32X1L 2
#define DRAMCONF_32X1H 3
#define DRAMCONF_256X1 4
#define MAX_DRAMCONF_1BIT 4
#define DRAMCONF_16X4 5
#define DRAMCONF_64X4 6
#define DRAMCONF_256X4 7
#ifndef _4M_DRAM_ENABLE
#define MAX_DRAMCONF 7
#else
#define DRAMCONF_1024X4 8
#define MAX_DRAMCONF 8
#endif

#define SCENE_SETTING_SELECT_ENTER 0
#define SCENE_SETTING_SELECT 1
#define SCENE_VIEW_12V 2
#define SCENE_VIEW_BTN 3
#define SCENE_DRAMCONF_SELECT_ENTER 4
#define SCENE_DRAMCONF_SELECT 5
#define SCENE_DRAM_TEST_ENTER 6
#define SCENE_DRAM_TEST 7

#define MIN_SETTINGMODE 0
#define SETTINGMODE_TESTTYPE_CHG 0
#define SETTINGMODE_POWSRCCHK_CHG 1
#define SETTINGMODE_EEPROM_ERASE 2
#define SETTINGMODE_POWER12V_VIEW 3
#define SETTINGMODE_BUTTON_VIEW 4
#define SETTINGMODE_EXIT 5
#define MAX_SETTINGMODE 5

#define DRAM_DQ1 14
#define DRAM_DQ2 15
#define DRAM_DQ3 16
#define DRAM_DQ4 17
#define DRAM_Q 14
#define DRAM_D 15
#define DRAM_A0 8
#define DRAM_A1 9
#define DRAM_A2 10
#define DRAM_A3 11
#define DRAM_A4 12
#define DRAM_A5 13
#define DRAM_A6 5
#define DRAM_A7 6
#define DRAM_A8 7
#define DRAM_RAS 2
#define DRAM_CAS 3
#define DRAM_W 4
#define BUTTON A6
#define POW12V A7
//      DRAM_OE GND

#define DRAM_D_PC_SHIFT (DRAM_D - 14)
#define DRAM_Q_PC_SHIFT (DRAM_Q - 14)
#define DRAM_DQ1_PC_SHIFT (DRAM_DQ1 - 14)
#define DRAM_DQ2_PC_SHIFT (DRAM_DQ2 - 14)
#define DRAM_DQ3_PC_SHIFT (DRAM_DQ3 - 14)
#define DRAM_DQ4_PC_SHIFT (DRAM_DQ4 - 14)
#define DRAM_DQ_PC_SHIFT DRAM_DQ1_PC_SHIFT
#define DRAM_A0_PB_SHIFT (DRAM_A0 - 8)
#define DRAM_A1_PB_SHIFT (DRAM_A1 - 8)
#define DRAM_A2_PB_SHIFT (DRAM_A2 - 8)
#define DRAM_A3_PB_SHIFT (DRAM_A3 - 8)
#define DRAM_A4_PB_SHIFT (DRAM_A4 - 8)
#define DRAM_A5_PB_SHIFT (DRAM_A5 - 8)
#define DRAM_A6_PD_SHIFT (DRAM_A6 - 0)
#define DRAM_A7_PD_SHIFT (DRAM_A7 - 0)
#define DRAM_A8_PD_SHIFT (DRAM_A8 - 0)
#define DRAM_A_PB_SHIFT (DRAM_A0 - 8)
#define DRAM_A_PD_SHIFT (DRAM_A6 - 0)
#define DRAM_RAS_PD_SHIFT (DRAM_RAS - 0)
#define DRAM_CAS_PD_SHIFT (DRAM_CAS - 0)
#define DRAM_W_PD_SHIFT (DRAM_W - 0)

#define DRAM_D_PC_MASK _BV(DRAM_D_PC_SHIFT)
#define DRAM_Q_PC_MASK _BV(DRAM_Q_PC_SHIFT)
#define DRAM_DQ_PC_MASK (_BV(DRAM_DQ1_PC_SHIFT) | _BV(DRAM_DQ2_PC_SHIFT) | _BV(DRAM_DQ3_PC_SHIFT) | _BV(DRAM_DQ4_PC_SHIFT))
#define DRAM_A_PB_MASK (_BV(DRAM_A0_PB_SHIFT) | _BV(DRAM_A1_PB_SHIFT) | _BV(DRAM_A2_PB_SHIFT) | _BV(DRAM_A3_PB_SHIFT) | _BV(DRAM_A4_PB_SHIFT) | _BV(DRAM_A5_PB_SHIFT))
#define DRAM_A_PD_MASK (_BV(DRAM_A6_PD_SHIFT) | _BV(DRAM_A7_PD_SHIFT) | _BV(DRAM_A8_PD_SHIFT))
#define DRAM_RAS_PD_MASK _BV(DRAM_RAS_PD_SHIFT)
#define DRAM_CAS_PD_MASK _BV(DRAM_CAS_PD_SHIFT)
#define DRAM_W_PD_MASK _BV(DRAM_W_PD_SHIFT)

#ifdef _BUS_A9_ENABLE
#define DRAM_A9 1
#define DRAM_A9_PD_SHIFT (DRAM_A9 - 0)
#define DRAM_A9_PD_MASK _BV(DRAM_A9_PD_SHIFT)
#endif

#define ANALOG_RESORUTION 1024.0
#define ANALOG_VALUE_LOW_MAX 164

#define VOLTAGE_5V0_MAX (5.0 * 1.05)
#define VOLTAGE_5V0_RATED 5.0
#define VOLTAGE_5V0_MIN (5.0 * 0.95)
#define VOLTAGE_12V0_MAX (12.0 * 1.05)
#define VOLTAGE_12V0_RATED 12.0
#define VOLTAGE_12V0_MIN (12.0 * 0.95)
#define VOLTAGE_3V3_MAX 3.6
#define VOLTAGE_3V3_RATED 3.3
#define VOLTAGE_3V3_MIN 3.0
#define VOLTAGE_12V0_CONVERT_COEFFICIENT (3.0 / ANALOG_RESORUTION)

#define EEPROM_UNERASE_SIZE (EEPROM.length() / 2)
#define EEPROM_IDX_ERASE_TOP (0)
#define EEPROM_IDX_DRAMCONF (EEPROM_IDX_ERASE_TOP + 0)
#define EEPROM_IDX_SPEEDYFLG (EEPROM_IDX_ERASE_TOP + 1)
#define EEPROM_IDX_POWSRCCHKFLG (EEPROM_IDX_ERASE_TOP + 2)
#define EEPROM_IDX_UNERASE_TOP (EEPROM.length() - EEPROM_UNERASE_SIZE)
#define EEPROM_IDX_CALIBVAL (EEPROM_IDX_UNERASE_TOP + 0)

#define MAX_DISP_5X8_LEN (128 / 5)
#define MAX_DISP_9X15_LEN (128 / 9)
#define DRAWNAME_BUF_SIZE (MAX_DISP_9X15_LEN + 1)
#define DRAWTEXT_BUF_SIZE (MAX_DISP_5X8_LEN + 1)

#define _delay_62p5ns asm("nop\n") // 1 clock wait at 16MHz -> 62.5ns
#define _delay_375ns asm("nop\nnop\nnop\nnop\nnop\nnop\n") // 6 clock wait at 16MHz -> 62.5ns x 6 = 375ns

inline int pseudoDigitalRead(uint8_t pin)
{
	return (analogRead(pin) <= ANALOG_VALUE_LOW_MAX) ? 0 : 1;
}

int8_t scene;
int8_t dramConfig;
int8_t settingMode;
byte lastBtn;
unsigned long pressedTime;
int8_t abus_size, nocol, colshift, colset;
bool speedyTest4bit, checkPowerGood5V;
int16_t calibrationValue;
bool powerGood12v, powerGood5v;
volatile double voltage5V0;
volatile double voltage12V0;

void waitButtonPressAndRelease(void)
{
	while (pseudoDigitalRead(BUTTON) == LOW)
		;
	while (pseudoDigitalRead(BUTTON) == HIGH)
		;
	while (pseudoDigitalRead(BUTTON) == LOW)
		;
}

bool checkPowerStatus(void)
{
	int av3v3 = analogRead(BUTTON);
	if (av3v3 > ANALOG_VALUE_LOW_MAX)
	{
		voltage5V0 = (double)calibrationValue / av3v3;
		powerGood5v = (voltage5V0 < VOLTAGE_5V0_MAX && voltage5V0 > VOLTAGE_5V0_MIN);
		voltage12V0 = VOLTAGE_12V0_CONVERT_COEFFICIENT * voltage5V0 * analogRead(POW12V);
		powerGood12v = (voltage12V0 < VOLTAGE_12V0_MAX && voltage12V0 > VOLTAGE_12V0_MIN);
		return true;
	}
	return false;
}

void setup(void)
{
	dispInit();
	disableDramBus();
#if 0
	// Caribration Value (3V3 actual voltage * 1024) write to EEPROM
	calibrationValue = 3.300 * ANALOG_RESORUTION;
	for (uint16_t i = 0; i < EEPROM.length(); i++)
	{
		EEPROM.update(i, -1);
	}
	EEPROM.put(EEPROM_IDX_CALIBVAL, calibrationValue);
#endif
	powerGood12v = false;
	powerGood5v = false;
	voltage5V0 = 0.0;
	voltage12V0 = 0.0;
	dramConfig = EEPROM.read(EEPROM_IDX_DRAMCONF);
	dramConfig = (dramConfig > MAX_DRAMCONF || dramConfig < MIN_DRAMCONF) ? DRAMCONF_64X1 : dramConfig;
	speedyTest4bit = (EEPROM.read(EEPROM_IDX_SPEEDYFLG) != 0);
	checkPowerGood5V = (EEPROM.read(EEPROM_IDX_POWSRCCHKFLG) != 0);

	EEPROM.get(EEPROM_IDX_CALIBVAL, calibrationValue);
	calibrationValue = calibrationValue > (VOLTAGE_3V3_MAX * ANALOG_RESORUTION) || calibrationValue < (VOLTAGE_3V3_MIN * ANALOG_RESORUTION) ? (VOLTAGE_3V3_RATED * ANALOG_RESORUTION) : calibrationValue;
	lastBtn = pseudoDigitalRead(BUTTON);
	if (lastBtn == LOW)
	{ // button is pressed
		settingMode = SETTINGMODE_TESTTYPE_CHG;
		settingModeDisp();
		scene = SCENE_SETTING_SELECT_ENTER;
	}
	else
	{
		checkPowerStatus();
		dramConfSelectDisp(false);
		lastBtn = LOW;
		scene = SCENE_DRAMCONF_SELECT_ENTER;
	}
}

void loop(void)
{
	unsigned long pressDuration;
	byte currentBtn;

	switch (scene)
	{
	case SCENE_SETTING_SELECT_ENTER:
		currentBtn = pseudoDigitalRead(BUTTON);
		if (lastBtn == LOW && currentBtn == HIGH)
		{ // button is released
			checkPowerStatus();
			lastBtn = HIGH;
			settingModeDisp();
			scene = SCENE_SETTING_SELECT;
		}
		break;
	case SCENE_SETTING_SELECT:
		currentBtn = pseudoDigitalRead(BUTTON);
		if (lastBtn == HIGH && currentBtn == LOW)
		{ // button is pressed
			lastBtn = LOW;
			pressedTime = millis();
		}
		pressDuration = millis() - pressedTime;
		if (lastBtn == LOW && currentBtn == HIGH)
		{ // button is released
			checkPowerStatus();
			lastBtn = HIGH;
			if (pressDuration < 1500)
			{ // short press
				settingMode++;
				settingMode = (settingMode > MAX_SETTINGMODE) ? MIN_SETTINGMODE : settingMode;
				settingModeDisp();
			}
		}
		if (lastBtn == LOW && currentBtn == LOW && pressDuration > 1500)
		{ // long press
			switch (settingMode)
			{
			case SETTINGMODE_TESTTYPE_CHG:
				speedyTest4bit = !speedyTest4bit;
				settingModeDisp();
				scene = SCENE_SETTING_SELECT_ENTER;
				break;
			case SETTINGMODE_POWSRCCHK_CHG:
				checkPowerGood5V = !checkPowerGood5V;
				settingModeDisp();
				scene = SCENE_SETTING_SELECT_ENTER;
				break;
			case SETTINGMODE_EEPROM_ERASE:
				eraseEepromDisp(false);
				for (uint16_t idx = 0; idx < EEPROM_IDX_UNERASE_TOP; idx++)
				{
					EEPROM.update(idx, -1);
				}
				speedyTest4bit = true;
				checkPowerGood5V = true;
				eraseEepromDisp(true);
				scene = SCENE_DRAMCONF_SELECT_ENTER;
				dramConfSelectDisp(false);
				break;
			case SETTINGMODE_POWER12V_VIEW:
				check12vModeDisp();
				scene = SCENE_VIEW_12V;
				break;
			case SETTINGMODE_BUTTON_VIEW:
				checkButtonModeDisp();
				scene = SCENE_VIEW_BTN;
				break;
			case SETTINGMODE_EXIT:
				if ((EEPROM.read(EEPROM_IDX_SPEEDYFLG) != 0 && !speedyTest4bit) || (EEPROM.read(EEPROM_IDX_SPEEDYFLG) == 0 && speedyTest4bit))
				{
					EEPROM.write(EEPROM_IDX_SPEEDYFLG, speedyTest4bit);
				}
				if ((EEPROM.read(EEPROM_IDX_POWSRCCHKFLG) != 0 && !checkPowerGood5V) || (EEPROM.read(EEPROM_IDX_POWSRCCHKFLG) == 0 && checkPowerGood5V))
				{
					EEPROM.write(EEPROM_IDX_POWSRCCHKFLG, checkPowerGood5V);
				}
				scene = SCENE_DRAMCONF_SELECT_ENTER;
				dramConfSelectDisp(false);
				break;
			}
		}
		break;
	case SCENE_VIEW_12V:
		checkPowerStatus();
		check12vModeDisp();
		scene = SCENE_VIEW_12V;
		break;
	case SCENE_VIEW_BTN:
		checkPowerStatus();
		checkButtonModeDisp();
		scene = SCENE_VIEW_BTN;
		break;
	case SCENE_DRAMCONF_SELECT_ENTER:
		currentBtn = pseudoDigitalRead(BUTTON);
		if (currentBtn == HIGH)
		{ // button is released
			lastBtn = HIGH;
			checkPowerStatus();
			dramConfSelectDisp(false);
			scene = SCENE_DRAMCONF_SELECT;
		}
		break;
	case SCENE_DRAMCONF_SELECT:
		currentBtn = pseudoDigitalRead(BUTTON);
		if (lastBtn == HIGH && currentBtn == LOW)
		{ // button is pressed
			lastBtn = LOW;
			pressedTime = millis();
		}
		pressDuration = millis() - pressedTime;
		if (lastBtn == LOW && currentBtn == HIGH)
		{ // button is released
			checkPowerStatus();
			lastBtn = HIGH;
			if (pressDuration < 1500)
			{ // short press
				dramConfig++;
				dramConfig = (dramConfig > MAX_DRAMCONF) ? MIN_DRAMCONF : dramConfig;
				dramConfSelectDisp(false);
			}
		}
		if (lastBtn == LOW && currentBtn == LOW && pressDuration > 1500)
		{ // long press
			dramConfSelectDisp(true);
			scene = SCENE_DRAM_TEST_ENTER;
		}
		break;
	case SCENE_DRAM_TEST_ENTER:
		currentBtn = pseudoDigitalRead(BUTTON);
		if (currentBtn == HIGH)
		{ // button is released
			lastBtn = HIGH;
			checkPowerStatus();
			if (!powerGood12v && dramConfig == DRAMCONF_16X1)
			{
				failedPower12vDisp();
				dramConfSelectDisp(false);
				scene = SCENE_DRAMCONF_SELECT_ENTER;
				break;
			}
			if (!powerGood5v && checkPowerGood5V)
			{
				failedPower5vDisp();
				dramConfSelectDisp(false);
				scene = SCENE_DRAMCONF_SELECT_ENTER;
				break;
			}
			dramConfSelectDisp(false);
			scene = SCENE_DRAM_TEST;
		}
		break;
	case SCENE_DRAM_TEST:
		EEPROM.update(0, dramConfig);
#ifndef _DEMO_MODE
		startDramTest();
#else
		passedTestDisp();
#endif
		scene = SCENE_DRAMCONF_SELECT_ENTER;
		break;
	}
}
