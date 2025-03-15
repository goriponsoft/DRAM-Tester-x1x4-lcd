#include <Arduino.h>
#include <EEPROM.h>

#include "Dram-Tester-x1x4-lcd.h"
#include "dramtest.h"
#include "display.h"

int8_t scene;
int8_t dramConfig;
int8_t settingMode;
byte lastBtn;
unsigned long pressedTime;
int8_t abus_size, nocol, colshift;
int colset, rowset;
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
	calibrationValue = calibrationValue > (int16_t)(VOLTAGE_3V3_MAX * ANALOG_RESORUTION) || calibrationValue < (int16_t)(VOLTAGE_3V3_MIN * ANALOG_RESORUTION) ? (int16_t)(VOLTAGE_3V3_RATED * ANALOG_RESORUTION) : calibrationValue;
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
		EEPROM.update(EEPROM_IDX_DRAMCONF, dramConfig);
#ifndef _DEMO_MODE
		startDramTest();
#else
		passedTestDisp();
#endif
		scene = SCENE_DRAMCONF_SELECT_ENTER;
		break;
	}
}
