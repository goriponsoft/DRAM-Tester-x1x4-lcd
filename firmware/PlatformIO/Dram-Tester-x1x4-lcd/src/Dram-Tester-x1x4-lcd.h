#ifndef _DRAM_TESTER_X1X4_LCD_H_
#define _DRAM_TESTER_X1X4_LCD_H_

#include <Arduino.h>

// #define _DEBUG			// Debug Function enable
// #define _DEMO_MODE		// Demo Mode firmware
//#define _BUS_A9_ENABLE	// Adress bus bit9 (PD1) enable
//#define _4M_DRAM_ENABLE	// 4M(1024Kx4) DRAM support enable. (_BUS_A9_ENABLE required.)

#define VERSION_STRING "1.0.0"
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

inline int pseudoDigitalRead(uint8_t pin)
{
	return (analogRead(pin) <= ANALOG_VALUE_LOW_MAX) ? 0 : 1;
}

extern int8_t scene;
extern int8_t dramConfig;
extern int8_t settingMode;
extern byte lastBtn;
extern unsigned long pressedTime;
extern int8_t abus_size, nocol, colshift;
extern int colset, rowset;
extern bool speedyTest4bit, checkPowerGood5V;
extern int16_t calibrationValue;
extern bool powerGood12v, powerGood5v;
extern volatile double voltage5V0;
extern volatile double voltage12V0;

extern void waitButtonPressAndRelease(void);
extern bool checkPowerStatus(void);

#endif
