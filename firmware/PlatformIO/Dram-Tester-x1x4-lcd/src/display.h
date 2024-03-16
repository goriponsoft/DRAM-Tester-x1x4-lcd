#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <U8g2lib.h>

#define MAX_DISP_5X8_LEN (128 / 5)
#define MAX_DISP_9X15_LEN (128 / 9)
#define DRAWNAME_BUF_SIZE (MAX_DISP_9X15_LEN + 1)
#define DRAWTEXT_BUF_SIZE (MAX_DISP_5X8_LEN + 1)

extern char *setDrawStr_P(char *, const char *);
extern char *catDrawStr_P(char *, const char *);
extern void setDrawFormatStr_P(char *, const char *, ...);
extern void u8g2_drawStr_P(u8g2_int_t, u8g2_int_t, const char *);
extern void u8g2_drawFormat_P(u8g2_int_t, u8g2_int_t, const char *, ...);

extern void dispInit(void);
extern void dramConfSelectDisp(bool);
extern void duringTestDisp(const char *, int, int, int);
extern void duringVerboseTestDisp(const char *, const char *);
extern void passedTestDisp(void);
extern void failedTestDisp(const char *, int, int);
extern void settingModeDisp(void);
extern void failedPower5vDisp(void);
extern void failedPower12vDisp(void);
extern void eraseEepromDisp(bool);
extern void check12vModeDisp();
extern void checkButtonModeDisp(void);

#endif
