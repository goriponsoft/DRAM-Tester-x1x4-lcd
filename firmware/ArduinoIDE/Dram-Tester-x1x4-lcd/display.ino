U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

static const char _str_code_0[] PROGMEM = "4116";
static const char _str_code_1[] PROGMEM = "4164";
static const char _str_code_2[] PROGMEM = "4532-3";
static const char _str_code_3[] PROGMEM = "4532-4";
static const char _str_code_4[] PROGMEM = "41256";
static const char _str_code_5[] PROGMEM = "4416";
static const char _str_code_6[] PROGMEM = "4464";
static const char _str_code_7[] PROGMEM = "44256";
#ifdef _4M_DRAM_ENABLE
static const char _str_code_8[] PROGMEM = "4400";
#endif
static const char *dramCodeStr[MAX_DRAMCONF + 1] = {
	_str_code_0,
	_str_code_1,
	_str_code_2,
	_str_code_3,
	_str_code_4,
	_str_code_5,
	_str_code_6,
	_str_code_7,
#ifdef _4M_DRAM_ENABLE
	_str_code_8,
#endif
};

static const char _str_config_0[] PROGMEM = "16Kx1";
static const char _str_config_1[] PROGMEM = "64Kx1";
static const char _str_config_2[] PROGMEM = "32Kx1-Low";
static const char _str_config_3[] PROGMEM = "32Kx1-High";
static const char _str_config_4[] PROGMEM = "256Kx1";
static const char _str_config_5[] PROGMEM = "16Kx4";
static const char _str_config_6[] PROGMEM = "64Kx4";
static const char _str_config_7[] PROGMEM = "256Kx4";
#ifdef _4M_DRAM_ENABLE
static const char _str_config_8[] PROGMEM = "1024Kx4";
#endif
static const char *dramConfigStr[MAX_DRAMCONF + 1] = {
	_str_config_0,
	_str_config_1,
	_str_config_2,
	_str_config_3,
	_str_config_4,
	_str_config_5,
	_str_config_6,
	_str_config_7,
#ifdef _4M_DRAM_ENABLE
	_str_config_8,
#endif
};

static const byte dramSocketNum[MAX_DRAMCONF + 1] = {
	0,
	1,
	1,
	1,
	1,
	2,
	2,
	3,
#ifdef _4M_DRAM_ENABLE
	3,
#endif
};

char *setDrawStr_P(char *d, const char *s)
{
	return strncpy_P(d, s, DRAWNAME_BUF_SIZE);
}

char *catDrawStr_P(char *d, const char *s)
{
	return strncat_P(d, s, DRAWNAME_BUF_SIZE);
}

void setDrawFormatStr_P(char *d, const char *fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	vsnprintf_P(d, DRAWTEXT_BUF_SIZE, fmt, list);
	va_end(list);
}

void u8g2_drawStr_P(u8g2_int_t x, u8g2_int_t y, const char *s)
{
	char drawtext[DRAWTEXT_BUF_SIZE];

	u8g2.drawStr(x, y, strncpy_P(drawtext, s, DRAWTEXT_BUF_SIZE));
}

void u8g2_drawFormat_P(u8g2_int_t x, u8g2_int_t y, const char *fmt, ...)
{
	va_list list;
	char drawtext[DRAWTEXT_BUF_SIZE];

	va_start(list, fmt);
	vsnprintf_P(drawtext, DRAWTEXT_BUF_SIZE, fmt, list);
	va_end(list);
	u8g2.drawStr(x, y, drawtext);
}

void dispInit(void)
{
	u8g2.begin();
	u8g2.clearBuffer();
}

void dramConfSelectDisp(bool entering)
{
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2_drawStr_P(0, 10, PSTR(NAME_STRING));
	u8g2.setFont(u8g2_font_5x8_mr);
	u8g2_drawStr_P(103, 10, PSTR(SUBNAME_STRING));
	u8g2_drawStr_P(0, 22, dramCodeStr[dramConfig]);
	u8g2_drawStr_P(35, 22, dramConfigStr[dramConfig]);
	u8g2_drawFormat_P(93, 22, PSTR("Socket%1d"), dramSocketNum[dramConfig]);
	if (entering)
		u8g2_drawStr_P(8, 31, PSTR("Release Button to Start."));
	u8g2.sendBuffer();
}

void duringTestDisp(const char *name, int value, int prognow, int progfin)
{
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2.drawStr(0, 10, name);
	u8g2.setFont(u8g2_font_5x8_mr);
	u8g2_drawFormat_P(0, 22, PSTR("Socket%1d"), dramSocketNum[dramConfig]);
	u8g2_drawStr_P(40, 22, dramCodeStr[dramConfig]);
	if (dramConfig > MAX_DRAMCONF_1BIT)
		u8g2_drawStr_P(75, 22, speedyTest4bit ? PSTR("Speedy") : PSTR("Strict"));
	u8g2_drawFormat_P(0, 31, PSTR("Value=%1X Progress=%d/%d"), value, prognow, progfin);
	interrupts();
	u8g2.sendBuffer();
	noInterrupts();
}

void duringVerboseTestDisp(const char *name, const char *text)
{
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2.drawStr(0, 10, name);
	u8g2.setFont(u8g2_font_5x8_mr);
	u8g2_drawFormat_P(0, 22, PSTR("Socket%1d"), dramSocketNum[dramConfig]);
	u8g2_drawStr_P(40, 22, dramCodeStr[dramConfig]);
	if (dramConfig > MAX_DRAMCONF_1BIT)
		u8g2_drawStr_P(75, 22, speedyTest4bit ? PSTR("Speedy") : PSTR("Strict"));
	if (text)
		u8g2.drawStr(0, 31, text);
	interrupts();
	u8g2.sendBuffer();
	noInterrupts();
}

void passedTestDisp(void)
{
	interrupts();
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2_drawStr_P(0, 10, PSTR("PASSED"));
	u8g2.setFont(u8g2_font_5x8_mr);
#ifdef _DEMO_MODE
	u8g2_drawStr_P(54 + 2, 10, PSTR(" * Demo Mode *"));
#endif
	u8g2_drawFormat_P(0, 22, PSTR("Socket%1d"), dramSocketNum[dramConfig]);
	u8g2_drawStr_P(40, 22, dramCodeStr[dramConfig]);
	if (dramConfig > MAX_DRAMCONF_1BIT)
		u8g2_drawStr_P(75, 22, speedyTest4bit ? PSTR("Speedy") : PSTR("Strict"));
	u8g2_drawStr_P(20, 31, PSTR("Press Button to Exit."));
	u8g2.sendBuffer();
	waitButtonPressAndRelease();
	delay(300);
}

void failedTestDisp(const char *name, int row, int col)
{
	interrupts();
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2_drawStr_P(0, 10, PSTR("FAILED"));
	u8g2.setFont(u8g2_font_5x8_mr);
	u8g2.drawStr(56, 10, name);
	u8g2_drawFormat_P(0, 22, PSTR("Socket%1d"), dramSocketNum[dramConfig]);
	u8g2_drawStr_P(40, 22, dramCodeStr[dramConfig]);
	u8g2_drawFormat_P(75, 22, PSTR("on %03X %03X"), col & ((1 << (abus_size - nocol)) - 1), row & ((1 << abus_size) - 1));
	u8g2_drawStr_P(20, 31, PSTR("Press Button to Exit."));
	u8g2.sendBuffer();
	waitButtonPressAndRelease();
	delay(300);
}

void settingModeDisp(void)
{
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2_drawStr_P(0, 10, PSTR(NAME_STRING));
	u8g2.setFont(u8g2_font_5x8_mr);
	u8g2_drawStr_P(103, 10, PSTR(VERSION_STRING));
	switch (settingMode)
	{
	case SETTINGMODE_TESTTYPE_CHG:
		u8g2_drawStr_P(0, 22, PSTR("4bit DRAM Test:"));
		u8g2_drawStr_P(80, 22, speedyTest4bit ? PSTR("Speedy") : PSTR("Strict"));
		// u8g2.drawStr(0, 31, "");
		break;
	case SETTINGMODE_POWSRCCHK_CHG:
		u8g2_drawStr_P(0, 22, PSTR("Power5V Voltage:"));
		u8g2_drawStr_P(85, 22, checkPowerGood5V ? PSTR("Check") : PSTR("Ignore"));
		u8g2_drawStr_P(0, 31, checkPowerGood5V ? PSTR(""): PSTR("*Tests may be inaccurate."));
		break;
	case SETTINGMODE_EEPROM_ERASE:
		u8g2_drawStr_P(0, 22, PSTR("Erase EEPROM"));
		u8g2_drawStr_P(0, 31, PSTR("*Setting will be exit."));
		break;
	case SETTINGMODE_POWER12V_VIEW:
		u8g2_drawStr_P(0, 22, PSTR("View Power12V"));
		u8g2_drawStr_P(0, 31, PSTR("*Only exit by reset."));
		break;
	case SETTINGMODE_BUTTON_VIEW:
		u8g2_drawStr_P(0, 22, PSTR("View Button & Power5V"));
		u8g2_drawStr_P(0, 31, PSTR("*Only exit by reset."));
		break;
	case SETTINGMODE_EXIT:
		u8g2_drawStr_P(0, 22, PSTR("Save and Exit"));
		u8g2_drawStr_P(0, 31, PSTR("*Not saved unless exit."));
		break;
	}
	u8g2.sendBuffer();
}

void failedPower5vDisp(void)
{
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2_drawStr_P(0, 10, PSTR("Failed 5V"));
	u8g2.setFont(u8g2_font_5x8_mr);
	u8g2_drawStr_P(81 + 2, 10, dramCodeStr[dramConfig]);
	u8g2_drawStr_P(0, 22, PSTR("AC-Adapter required."));
	u8g2_drawStr_P(20, 31, PSTR("Press Button to Exit."));
	u8g2.sendBuffer();
	waitButtonPressAndRelease();
	delay(300);
}

void failedPower12vDisp(void)
{
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2_drawStr_P(0, 10, PSTR("Failed 12V"));
	u8g2.setFont(u8g2_font_5x8_mr);
	u8g2_drawStr_P(90 + 2, 10, dramCodeStr[dramConfig]);
	u8g2_drawStr_P(0, 22, PSTR("Adjustment required."));
	u8g2_drawStr_P(20, 31, PSTR("Press Button to Exit."));
	u8g2.sendBuffer();
	waitButtonPressAndRelease();
	delay(300);
}

void eraseEepromDisp(bool finished)
{
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2_drawStr_P(0, 10, PSTR("EEPROM"));
	u8g2.setFont(u8g2_font_5x8_mr);
	if (finished)
	{
		u8g2_drawStr_P(0, 22, PSTR("Erase complete."));
		u8g2_drawStr_P(20, 31, PSTR("Press Button to Exit."));
	}
	else
	{
		u8g2_drawStr_P(0, 22, PSTR("Erasing..."));
	}
	u8g2.sendBuffer();
	if (finished) {
		waitButtonPressAndRelease();
		delay(300);
	}
}

void check12vModeDisp(void)
{
	int av12v = analogRead(POW12V);
	int mv12v = (int)(voltage12V0 * 10);
	int err5v = (int)((voltage5V0 - VOLTAGE_5V0_RATED) * 1000 / VOLTAGE_5V0_RATED);
	int err12v = (int)((voltage12V0 - VOLTAGE_12V0_RATED) * 1000 / VOLTAGE_12V0_RATED);
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2_drawStr_P(0, 10, PSTR("12V Chk."));
	u8g2.setFont(u8g2_font_5x8_mr);
	u8g2_drawFormat_P(0, 22, PSTR("ValueA7:%4d err5V:%+2d.%1d%%"), av12v, err5v / 10, abs(err5v) % 10);
	u8g2_drawFormat_P(0, 31, PSTR("Voltage:%2d.%1dV err:%+2d.%1d%%"), mv12v / 10, mv12v % 10, err12v / 10, abs(err12v) % 10);
	u8g2.sendBuffer();
}

void checkButtonModeDisp(void)
{
	int avBtn = analogRead(BUTTON);
	int btn = pseudoDigitalRead(BUTTON);
	int mv5v = (int)(voltage5V0 * 10);
	int err = (int)((voltage5V0 - VOLTAGE_5V0_RATED) * 1000 / VOLTAGE_5V0_RATED);
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x15_mr);
	u8g2_drawStr_P(0, 10, PSTR("Btn & 5V Chk."));
	u8g2.setFont(u8g2_font_5x8_mr);
	u8g2_drawFormat_P(0, 22, PSTR("ValueA6:%4d %c"), avBtn, btn == LOW ? 'L' : 'H');
	u8g2_drawStr_P(105, 22, powerGood5v ? PSTR("Good") : PSTR("Bad"));
	u8g2_drawFormat_P(0, 31, PSTR("Voltage:%1d.%1dV err:%+2d.%1d%%"), mv5v / 10, mv5v % 10, err / 10, abs(err) % 10);
	u8g2.sendBuffer();
}
