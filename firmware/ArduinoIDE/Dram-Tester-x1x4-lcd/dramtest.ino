inline void prepareTest4(void)
{
	// PC0-PC3 Input, PC4-PC6 keep state
	// (Since the settings change when getDataBus4() and setDataBus4() are executed, the settings here are normally unnecessary.)
	DDRC &= ~DRAM_DQ_PC_MASK;
}

inline void prepareWrite4(void)
{
	// PC0-PC3 Output, PC4-PC6 keep state
	DDRC |= DRAM_DQ_PC_MASK;
	/*
	pinMode(DRAM_DQ1, OUTPUT);
	pinMode(DRAM_DQ2, OUTPUT);
	pinMode(DRAM_DQ3, OUTPUT);
	pinMode(DRAM_DQ4, OUTPUT);
	*/
}

inline void setDataBus4(int value)
{
	PORTC = (PORTC & ~DRAM_DQ_PC_MASK) | ((value << DRAM_DQ_PC_SHIFT) & DRAM_DQ_PC_MASK);
	/*
	digitalWrite(DRAM_DQ1, (value >> 0) & 1);
	digitalWrite(DRAM_DQ2, (value >> 1) & 1);
	digitalWrite(DRAM_DQ3, (value >> 2) & 1);
	digitalWrite(DRAM_DQ4, (value >> 3) & 1);
	*/
}

inline void prepareRead4(void)
{
	// PC0-PC3 Not pull-up, PC4-PC6 keep state
	// Clearing the pull-up setting is required regardless of whether the pinMode() function is used. (Test will start without any IC inserted into the socket.)
	PORTC &= ~DRAM_DQ_PC_MASK;
	// PC0-PC3 Input, PC4-PC6 keep state
	DDRC &= ~DRAM_DQ_PC_MASK;
	/*
	PORTC &= ~DRAM_DQ_PC_MASK;
	pinMode(DRAM_DQ1, INPUT);
	pinMode(DRAM_DQ2, INPUT);
	pinMode(DRAM_DQ3, INPUT);
	pinMode(DRAM_DQ4, INPUT);
	*/
}

inline int getDataBus4(void)
{
	// PC0-3 to return value bit0-3
	return (PINC & DRAM_DQ_PC_MASK) >> DRAM_DQ_PC_SHIFT;
	/*
	return	(digitalRead(DRAM_DQ1) << 0) |
			(digitalRead(DRAM_DQ2) << 1) |
			(digitalRead(DRAM_DQ3) << 2) |
			(digitalRead(DRAM_DQ4) << 3);
	*/
}

inline void prepareTest1(void)
{
	// PC0 Not pull-up, PC1-PC6 keep state
	// Clearing the pull-up setting is required regardless of whether the pinMode() function is used. (Test will start without any IC inserted into the socket.)
	PORTC &= ~DRAM_Q_PC_MASK;
	// PC0 Input, PC1 Output, PC2-PC6 keep state
	DDRC = (DDRC & ~DRAM_Q_PC_MASK) | DRAM_D_PC_MASK;
	/*
	pinMode(DRAM_Q, INPUT);
	pinMode(DRAM_D, OUTPUT);
	*/
}

inline void prepareWrite1(void)
{
	// PC1 Output, PC0 & PC2-PC6 keep state
	// (Since the settings are fixed from prepareTest1(), the settings here are originally unnecessary.)
	DDRC |= DRAM_D_PC_MASK;
	/*
	pinMode(DRAM_D, OUTPUT);
	*/
}

inline void setDataBus1(int value)
{
	PORTC = (PORTC & ~DRAM_D_PC_MASK) | ((value << DRAM_D_PC_SHIFT) & DRAM_D_PC_MASK);
	/*
	digitalWrite(DRAM_D, value & 1);
	*/
}

inline void prepareRead1(void)
{
	// PC0 Input, PC1-PC6 keep state
	// (Since the settings are fixed from prepareTest1(), the settings here are originally unnecessary.)
	DDRC &= ~DRAM_Q_PC_MASK;
	/*
	pinMode(DRAM_Q, INPUT);
	*/
}

inline int getDataBus1(void)
{
	return (PINC & DRAM_Q_PC_MASK) >> DRAM_Q_PC_SHIFT;
	/*
	return digitalRead(DRAM_Q);
	*/
}

inline void enableDramBus(void)
{
	// PD2-PD7 Output, PD0-PD1 keep state
	DDRD |= DRAM_A_PD_MASK | DRAM_RAS_PD_MASK | DRAM_CAS_PD_MASK | DRAM_W_PD_MASK;
	// PD2-PD4 HIGH, PD0-PD1 & PD5-PD7 keep state
	PORTD |= DRAM_W_PD_MASK | DRAM_CAS_PD_MASK | DRAM_RAS_PD_MASK;
	// PB0-PB5 Output, other bits keep state
	DDRB |= DRAM_A_PB_MASK;
	// PC0-PC3 Not pull-up, PC4-PC5 & other bits keep state
	PORTC &= ~DRAM_DQ_PC_MASK;
	// PC0-PC3 Input, PC4-PC5 & other bits keep state
	DDRC &= ~DRAM_DQ_PC_MASK;
#ifdef _BUS_A9_ENABLE
	// PD1 Output, PD0 & PD2-PD7 keep state
	DDRD |= DRAM_A9_PD_MASK;
#endif
	/*
	for (int pin = 2; pin < 14; pin++)
		pinMode(pin, OUTPUT);
#ifdef _BUS_A9_ENABLE
	pinMode(DRAM_A9, OUTPUT);
#endif
	digitalWrite(DRAM_W, HIGH);
	digitalWrite(DRAM_CAS, HIGH);
	digitalWrite(DRAM_RAS, HIGH);
	for (int pin = 14; pin < 18; pin++)
		pinMode(pin, INPUT);
	*/
}

inline void disableDramBus(void)
{
	// PD2-PD7 Not pull-up, PD0-1 keep state
	PORTD &= ~(DRAM_A_PD_MASK | DRAM_RAS_PD_MASK | DRAM_CAS_PD_MASK | DRAM_W_PD_MASK);
	// PD2-PD7 Input, PD0-1 keep state
	DDRD &= ~(DRAM_A_PD_MASK | DRAM_RAS_PD_MASK | DRAM_CAS_PD_MASK | DRAM_W_PD_MASK);
	// PB0-PB5 Not pull-up, other bits keep state
	PORTB &= ~DRAM_A_PB_MASK;
	// PB0-PB5 Input, other bits keep state
	DDRB &= ~DRAM_A_PB_MASK;
	// PC0-PC3 Not pull-up, PC4-PC5 & other bits keep state
	PORTC &= ~DRAM_DQ_PC_MASK;
	// PC0-PC3 Input, PC4-PC5 & other bits keep state
	DDRC &= ~DRAM_DQ_PC_MASK;
#ifdef _BUS_A9_ENABLE
	// PD1 Not pull-up, PD0 & PD2-PD7 keep state
	PORTD &= ~DRAM_A9_PD_MASK;
	// PD1 Input, PD0 & PD2-PD7 keep state
	DDRD &= ~DRAM_A9_PD_MASK;
#endif
	/*
	for (int pin = 2; pin < 18; pin++)
		pinMode(pin, INPUT);
#ifdef _BUS_A9_ENABLE
	pinMode(DRAM_A9, INPUT);
#endif
	*/
}

inline void setAddressBus(int adr)
{
	// bit0-5 to PB0-5
	PORTB = (PORTB & ~DRAM_A_PB_MASK) | (((adr >> 0) << DRAM_A_PB_SHIFT) & DRAM_A_PB_MASK);
	// bit6-8 to PD5-7
	PORTD = (PORTD & ~DRAM_A_PD_MASK) | (((adr >> 6) << DRAM_A_PD_SHIFT) & DRAM_A_PD_MASK);
#ifdef _BUS_A9_ENABLE
	// bit9 to PD1
	PORTD = (PORTD & ~DRAM_A9_PD_MASK) | (((adr >> 9) << DRAM_A9_PD_SHIFT) & DRAM_A9_PD_MASK);
#endif
	/*
	digitalWrite(DRAM_A0, (adr >> 0) & 1);
	digitalWrite(DRAM_A1, (adr >> 1) & 1);
	digitalWrite(DRAM_A2, (adr >> 2) & 1);
	digitalWrite(DRAM_A3, (adr >> 3) & 1);
	digitalWrite(DRAM_A4, (adr >> 4) & 1);
	digitalWrite(DRAM_A5, (adr >> 5) & 1);
	digitalWrite(DRAM_A6, (adr >> 6) & 1);
	digitalWrite(DRAM_A7, (adr >> 7) & 1);
	digitalWrite(DRAM_A8, (adr >> 8) & 1);
#ifdef _BUS_A9_ENABLE
	digitalWrite(DRAM_A9, (adr >> 9) & 1);
#endif
	*/
}

inline void writeDram1(int row, int col, int value)
{
	prepareWrite1();
	setAddressBus(row);
	PORTD &= ~DRAM_RAS_PD_MASK;
	PORTD &= ~DRAM_W_PD_MASK;
	/*
	digitalWrite(DRAM_RAS, LOW);
	digitalWrite(DRAM_W, LOW);
	*/
	setDataBus1(value);
	setAddressBus(col);
	PORTD &= ~DRAM_CAS_PD_MASK;
	_delay_375ns;
	PORTD |= DRAM_W_PD_MASK;
	PORTD |= DRAM_CAS_PD_MASK;
	PORTD |= DRAM_RAS_PD_MASK;
	/*
	digitalWrite(DRAM_CAS, LOW);
	digitalWrite(DRAM_W, HIGH);
	digitalWrite(DRAM_CAS, HIGH);
	digitalWrite(DRAM_RAS, HIGH);
	*/
}

inline void writeDram4(int row, int col, int value)
{
	prepareWrite4();
	setAddressBus(row);
	PORTD &= ~DRAM_RAS_PD_MASK;
	PORTD &= ~DRAM_W_PD_MASK;
	/*
	digitalWrite(DRAM_RAS, LOW);
	digitalWrite(DRAM_W, LOW);
	*/
	setDataBus4(value);
	setAddressBus(col);
	PORTD &= ~DRAM_CAS_PD_MASK;
	_delay_375ns;
	PORTD |= DRAM_W_PD_MASK;
	PORTD |= DRAM_CAS_PD_MASK;
	PORTD |= DRAM_RAS_PD_MASK;
	/*
	digitalWrite(DRAM_CAS, LOW);
	digitalWrite(DRAM_W, HIGH);
	digitalWrite(DRAM_CAS, HIGH);
	digitalWrite(DRAM_RAS, HIGH);
	*/
}

inline int readDram1(int row, int col)
{
	prepareRead1();
	setAddressBus(row);
	PORTD &= ~DRAM_RAS_PD_MASK;
	/*
	digitalWrite(DRAM_RAS, LOW);
	*/
	setAddressBus(col);
	PORTD &= ~DRAM_CAS_PD_MASK;
	_delay_375ns;
	/*
	digitalWrite(DRAM_CAS, LOW);
	*/
	int ret = getDataBus1();
	PORTD |= DRAM_CAS_PD_MASK;
	PORTD |= DRAM_RAS_PD_MASK;
	/*
	digitalWrite(DRAM_CAS, HIGH);
	digitalWrite(DRAM_RAS, HIGH);
	*/
	return ret;
}

inline int readDram4(int row, int col)
{
	prepareRead4();
	setAddressBus(row);
	PORTD &= ~DRAM_RAS_PD_MASK;
	/*
	digitalWrite(DRAM_RAS, LOW);
	*/
	setAddressBus(col);
	PORTD &= ~DRAM_CAS_PD_MASK;
	_delay_375ns;
	/*
	digitalWrite(DRAM_CAS, LOW);
	*/
	int ret = getDataBus4();
	PORTD |= DRAM_CAS_PD_MASK;
	PORTD |= DRAM_RAS_PD_MASK;
	/*
	digitalWrite(DRAM_CAS, HIGH);
	digitalWrite(DRAM_RAS, HIGH);
	*/
	return ret;
}

inline void setupDram(void)
{
	_delay_us(250);
	setAddressBus(0);
	for (int i = 0; i < 8; i++)
	{
		PORTD &= ~DRAM_RAS_PD_MASK;
		PORTD |= DRAM_RAS_PD_MASK;
		/*
		digitalWrite(DRAM_RAS, LOW);
		digitalWrite(DRAM_RAS, HIGH);
		*/
	}
}

inline void setupBus(void)
{
	enableDramBus();
	abus_size = 8;
	nocol = 0;
	colshift = 0;
	colset = 0;
	if (dramConfig <= MAX_DRAMCONF_1BIT)
	{ // 1bit DRAM
		prepareTest1();
		switch (dramConfig)
		{
		case DRAMCONF_16X1:
			abus_size = 7;
			// nocol = 0;
			// colshift = 0;
			// colset = 0;
			break;
		case DRAMCONF_32X1L:
			// abus_size = 8;
			nocol = 1;
			// colshift = 0;
			colset = 0 << 7;
			break;
		case DRAMCONF_32X1H:
			// abus_size = 8;
			nocol = 1;
			// colshift = 0;
			colset = 1 << 7;
			break;
		case DRAMCONF_256X1:
			abus_size = 9;
			// nocol = 0;
			// colshift = 0;
			// colset = 0;
			break;
		default:
			break;
		}
	}
	else
	{ // 4bit DRAM
		prepareTest4();
		switch (dramConfig)
		{
		case DRAMCONF_16X4:
			// abus_size = 8;
			nocol = 2;
			colshift = 1;
			// colset = 0;
			break;
		case DRAMCONF_256X4:
			abus_size = 9;
			// nocol = 0;
			// colshift = 0;
			// colset = 0;
			break;
#ifdef _4M_DRAM_ENABLE
		case DRAMCONF_1024X4:
			abus_size = 10;
			// nocol = 0;
			// colshift = 0;
			// colset = 0;
			break;
#endif
		default:
			break;
		}
	}
}

bool testWriteAndVerify1(const char *testname, int value)
{
	for (int c = 0; c < (1 << (abus_size - nocol)); c++)
	{
		int col = (c | colset) << colshift;
		for (int row = 0; row < (1 << abus_size); row++)
		{
			writeDram1(row, col, value);
			if (value != readDram1(row, col))
			{
				disableDramBus();
				failedTestDisp(testname, row, c);
				return true;
			}
		}
	}
	return false;
}

bool testWriteAndVerify4(const char *testname, int value)
{
	for (int c = 0; c < (1 << (abus_size - nocol)); c++)
	{
		int col = (c | colset) << colshift;
		for (int row = 0; row < (1 << abus_size); row++)
		{
			writeDram4(row, col, value);
			if (value != readDram4(row, col))
			{
				disableDramBus();
				failedTestDisp(testname, row, c);
				return true;
			}
		}
	}
	return false;
}

bool testWriteAndVerifyAlternatelyInvert1(const char *testname, int value)
{
	value &= 1;
	for (int c = 0; c < (1 << (abus_size - nocol)); c++)
	{
		int col = (c | colset) << colshift;
		for (int row = 0; row < (1 << abus_size); row++)
		{
			writeDram1(row, col, value);
			if (value != readDram1(row, col))
			{
				disableDramBus();
				failedTestDisp(testname, row, c);
				return true;
			}
			value ^= 1;
		}
	}
	return false;
}

bool testWriteAndVerifyAlternatelyInvert4(const char *testname, int value)
{
	value &= 0xf;
	for (int c = 0; c < (1 << (abus_size - nocol)); c++)
	{
		int col = (c | colset) << colshift;
		for (int row = 0; row < (1 << abus_size); row++)
		{
			writeDram4(row, col, value);
			if (value != readDram4(row, col))
			{
				disableDramBus();
				failedTestDisp(testname, row, c);
				return true;
			}
			value ^= 0xf;
		}
	}
	return false;
}

bool testWriteOnly1(int value)
{
	for (int c = 0; c < (1 << (abus_size - nocol)); c++)
	{
		int col = (c | colset) << colshift;
		for (int row = 0; row < (1 << abus_size); row++)
		{
			writeDram1(row, col, value);
		}
	}
	return false;
}

bool testWriteOnly4(int value)
{
	for (int c = 0; c < (1 << (abus_size - nocol)); c++)
	{
		int col = (c | colset) << colshift;
		for (int row = 0; row < (1 << abus_size); row++)
		{
			writeDram4(row, col, value);
		}
	}
	return false;
}

bool testVerifyOnly1(const char *testname, int value)
{
	for (int c = 0; c < (1 << (abus_size - nocol)); c++)
	{
		int col = (c | colset) << colshift;
		for (int row = 0; row < (1 << abus_size); row++)
		{
			if (value != readDram1(row, col))
			{
				disableDramBus();
				failedTestDisp(testname, row, c);
				return true;
			}
		}
	}
	return false;
}

bool testVerifyOnly4(const char *testname, int value)
{
	for (int c = 0; c < (1 << (abus_size - nocol)); c++)
	{
		int col = (c | colset) << colshift;
		for (int row = 0; row < (1 << abus_size); row++)
		{
			if (value != readDram4(row, col))
			{
				disableDramBus();
				failedTestDisp(testname, row, c);
				return true;
			}
		}
	}
	return false;
}

bool testRowAddress1(const char *testname, int value)
{
	int br, cr, row;
	value &= 1;
	testWriteOnly1(value);
	for (br = 0; br < abus_size + 1; br++)
	{
		row = _BV(br) >> 1;
		writeDram1(row, 0, value ^ 1);
		for (cr = 0; cr <= br; cr++)
		{
			row = _BV(cr) >> 1;
			if (readDram1(row, 0) != (value ^ 1))
			{
				disableDramBus();
				failedTestDisp(testname, row, 0);
				return true;
			}
		}
		for (; cr < abus_size + 1; cr++)
		{
			row = _BV(cr) >> 1;
			if (readDram1(row, 0) != value)
			{
				disableDramBus();
				failedTestDisp(testname, row, 0);
				return true;
			}
		}
	}
	for (row = 3; row < _BV(abus_size); row++)
	{
		bool skip = false;
		for (cr = 2; cr < abus_size; cr++)
		{
			if (row == _BV(cr))
			{
				skip = true;
				break;
			}
		}
		if (skip)
			continue;
		if (readDram1(row, 0) != value)
		{
			disableDramBus();
			failedTestDisp(testname, row, 0);
			return true;
		}
	}
	return false;
}

bool testColAddress1(const char *testname, int value)
{
	int bc, cc, col;
	value &= 1;
	testWriteOnly1(value);
	for (bc = 0; bc < abus_size - nocol + 1; bc++)
	{
		col = _BV(bc) >> 1;
		writeDram1(0, (col | colset) << colshift, value ^ 1);
		for (cc = 0; cc <= bc; cc++)
		{
			col = _BV(cc) >> 1;
			if (readDram1(0, (col | colset) << colshift) != (value ^ 1))
			{
				disableDramBus();
				failedTestDisp(testname, 0, col);
				return true;
			}
		}
		for (; cc < abus_size - nocol + 1; cc++)
		{
			col = _BV(cc) >> 1;
			if (readDram1(0, (col | colset) << colshift) != value)
			{
				disableDramBus();
				failedTestDisp(testname, 0, col);
				return true;
			}
		}
	}
	for (col = 3; col < _BV(abus_size - nocol); col++)
	{
		bool skip = false;
		for (cc = 2; cc < abus_size - nocol; cc++)
		{
			if (col == _BV(cc))
			{
				skip = true;
				break;
			}
		}
		if (skip)
			continue;
		if (readDram1(0, (col | colset) << colshift) != value)
		{
			disableDramBus();
			failedTestDisp(testname, 0, col);
			return true;
		}
	}
	return false;
}

bool testRowAddress4(const char *testname, int value)
{
	int br, cr, row;
	value &= 0xf;
	testWriteOnly4(value);
	for (br = 0; br < abus_size + 1; br++)
	{
		row = _BV(br) >> 1;
		writeDram4(row, 0, value ^ 0xf);
		for (cr = 0; cr <= br; cr++)
		{
			row = _BV(cr) >> 1;
			if (readDram4(row, 0) != (value ^ 0xf))
			{
				disableDramBus();
				failedTestDisp(testname, row, 0);
				return true;
			}
		}
		for (; cr < abus_size + 1; cr++)
		{
			row = _BV(cr) >> 1;
			if (readDram4(row, 0) != value)
			{
				disableDramBus();
				failedTestDisp(testname, row, 0);
				return true;
			}
		}
	}
	for (row = 3; row < _BV(abus_size); row++)
	{
		bool skip = false;
		for (cr = 2; cr < abus_size; cr++)
		{
			if (row == _BV(cr))
			{
				skip = true;
				break;
			}
		}
		if (skip)
			continue;
		if (readDram4(row, 0) != value)
		{
			disableDramBus();
			failedTestDisp(testname, row, 0);
			return true;
		}
	}
	return false;
}

bool testColAddress4(const char *testname, int value)
{
	int bc, cc, col;
	value &= 0xf;
	testWriteOnly4(value);
	for (bc = 0; bc < abus_size - nocol; bc++)
	{
		col = _BV(bc) >> 1;
		writeDram4(0, (col | colset) << colshift, value ^ 0xf);
		for (cc = 0; cc <= bc; cc++)
		{
			col = _BV(cc) >> 1;
			if (readDram4(0, (col | colset) << colshift) != (value ^ 0xf))
			{
				disableDramBus();
				failedTestDisp(testname, -1, col);
				return true;
			}
		}
		for (; cc < abus_size - nocol; cc++)
		{
			col = _BV(cc) >> 1;
			if (readDram4(0, (col | colset) << colshift) != value)
			{
				disableDramBus();
				failedTestDisp(testname, -1, col);
				return true;
			}
		}
	}
	for (col = 3; col < _BV(abus_size - nocol); col++)
	{
		bool skip = false;
		for (cc = 2; cc < abus_size - nocol; cc++)
		{
			if (col == _BV(cc))
			{
				skip = true;
				break;
			}
		}
		if (skip)
			continue;
		if (readDram4(0, (col | colset) << colshift) != value)
		{
			disableDramBus();
			failedTestDisp(testname, 0, col);
			return true;
		}
	}
	return false;
}

void startDramTest(void)
{
	char name[DRAWNAME_BUF_SIZE];
	byte val, maxvals;
	bool isFailed = false;

	/*
	checkPowerStatus();
	if (!powerGood12v && dramConfig == DRAMCONF_16X1)
	{
		failedPower12vDisp();
		waitButtonPressAndRelease();
		delay(300);
		dramConfig++;
		dramConfSelectDisp(false);
		return;
	}
	if (!powerGood5v && checkPowerGood5V)
	{
		failedPower5vDisp();
		waitButtonPressAndRelease();
		delay(300);
		dramConfSelectDisp(false);
		return;
	}
	*/

	setupBus();
	setupDram();
	if (!isFailed)
	{
		setDrawStr_P(name, PSTR("StartingTest"));
		if (dramConfig <= MAX_DRAMCONF_1BIT)
		{
			duringTestDisp(name, 1, 1, 1);
			isFailed = testWriteAndVerify1(name, 1);
		}
		else
		{
			duringTestDisp(name, 0xf, 1, 1);
			isFailed = testWriteAndVerify4(name, 0xf);
		}
	}
	if (!isFailed)
	{
		setDrawStr_P(name, PSTR("AdrsTest Row"));
		if (dramConfig <= MAX_DRAMCONF_1BIT)
		{
			duringTestDisp(name, 1, 1, 2);
			isFailed = testRowAddress1(name, 1);
		}
		else
		{
			duringTestDisp(name, 0xf, 1, 2);
			isFailed = testRowAddress4(name, 0xf);
		}
	}
	if (!isFailed)
	{
		setDrawStr_P(name, PSTR("AdrsTest Col"));
		if (dramConfig <= MAX_DRAMCONF_1BIT)
		{
			duringTestDisp(name, 1, 2, 2);
			isFailed = testColAddress1(name, 1);
		}
		else
		{
			duringTestDisp(name, 0xf, 2, 2);
			isFailed = testColAddress4(name, 0xf);
		}
	}
	if (dramConfig <= MAX_DRAMCONF_1BIT)
	{
		for (int i = 0; i < 2; i++)
		{
			if (!isFailed)
			{
				setDrawStr_P(name, PSTR("WordTest"));
				duringTestDisp(name, i, 1 + i, 2);
				isFailed = testWriteAndVerifyAlternatelyInvert1(name, i);
			}
		}
	}
	else
	{
		byte vals[] = {0, 0xf, 0x5, 0xa, 0xc, 0x3, 0x9, 0x6};
		maxvals = speedyTest4bit ? 2 : sizeof(vals);
		for (int i = 0; i < maxvals; i++)
		{
			if (!isFailed)
			{
				val = vals[i];
				setDrawStr_P(name, PSTR("WordTest"));
				duringTestDisp(name, val, 1 + i, maxvals);
				isFailed = testWriteAndVerifyAlternatelyInvert4(name, val);
			}
		}
	}
	if (dramConfig <= MAX_DRAMCONF_1BIT)
	{
		for (int i = 0; i < 2; i++)
		{
			if (!isFailed)
			{
				setDrawStr_P(name, PSTR("FullTestWrite"));
				duringTestDisp(name, i, 1 + i, 2);
				isFailed = testWriteOnly1(i);
				setDrawStr_P(name, PSTR("FullTestVerify"));
				duringTestDisp(name, i, 1 + i, 2);
				isFailed = testVerifyOnly1(name, i);
			}
		}
	}
	else
	{
		byte vals[] = {0x5, 0xa, 0xc, 0x3, 0x9, 0x6};
		maxvals = speedyTest4bit ? 2 : sizeof(vals);
		for (int i = 0; i < maxvals; i++)
		{
			if (!isFailed)
			{
				val = vals[i];
				duringTestDisp(name, val, i + 1, maxvals);
				setDrawStr_P(name, PSTR("FullTestWrite"));
				duringTestDisp(name, val, i + 1, maxvals);
				isFailed = testWriteOnly4(val);
				setDrawStr_P(name, PSTR("FullTestVerify"));
				duringTestDisp(name, val, i + 1, maxvals);
				isFailed = testVerifyOnly4(name, val);
			}
		}
	}
	if (!isFailed)
	{
		setDrawStr_P(name, PSTR("FinishingTest"));
		if (dramConfig <= MAX_DRAMCONF_1BIT)
		{
			duringTestDisp(name, 0, 1, 1);
			isFailed = testWriteAndVerify1(name, 0);
		}
		else
		{
			duringTestDisp(name, 0, 1, 1);
			isFailed = testWriteAndVerify4(name, 0);
		}
	}
	interrupts();
	disableDramBus();
	if (!isFailed)
	{
		passedTestDisp();
	}
	dramConfSelectDisp(false);
}

void startVerboseDramTest(void)
{
	char name[DRAWNAME_BUF_SIZE], text[DRAWTEXT_BUF_SIZE];
	setupBus();
	setupDram();
	if (dramConfig <= MAX_DRAMCONF_1BIT)
	{
		for (int c = 0; c < (1 << (abus_size - nocol)); c++)
		{
			for (int row = 0; row < (1 << abus_size); row++)
			{
				int col = (c | colset) << colshift;
				int rvb = readDram1(row, col);
				int wv = rvb ^ 1;
				writeDram1(row, col, wv);
				int rva = readDram1(row, col);
				setDrawStr_P(name, PSTR("VerboseTinyTst"));
				setDrawFormatStr_P(text, PSTR("c%03X r%03X b%1X w%1X a%1X "), c, row, rvb, wv, rva);
				catDrawStr_P(text, (wv != rva) ? PSTR("fail") : PSTR("pass"));
				duringVerboseTestDisp(name, text);
				if (wv != rva)
					waitButtonPressAndRelease();
			}
		}
	}
	else
	{
		for (int c = 0; c < (1 << (abus_size - nocol)); c++)
		{
			for (int row = 0; row < (1 << abus_size); row++)
			{
				int col = (c | colset) << colshift;
				int rvb = readDram4(row, col);
				int wv = rvb ^ 0xf;
				writeDram4(row, col, wv);
				int rva = readDram4(row, col);
				setDrawStr_P(name, PSTR("VerboseTinyTst"));
				setDrawFormatStr_P(text, PSTR("c%03X r%03X b%1X w%1X a%1X "), c, row, rvb, wv, rva);
				catDrawStr_P(text, (wv != rva) ? PSTR("fail") : PSTR("pass"));
				duringVerboseTestDisp(name, text);
				if (wv != rva)
					waitButtonPressAndRelease();
			}
		}
	}
}