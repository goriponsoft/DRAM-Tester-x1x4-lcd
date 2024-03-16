#ifndef _DRAMTEST_H_
#define _DRAMTEST_H_

#define _delay_62p5ns asm("nop\n")						   // 1 clock wait at 16MHz -> 62.5ns
#define _delay_375ns asm("nop\nnop\nnop\nnop\nnop\nnop\n") // 6 clock wait at 16MHz -> 62.5ns x 6 = 375ns

extern void disableDramBus(void);
extern void startDramTest(void);
extern void startVerboseDramTest(void);

#endif
