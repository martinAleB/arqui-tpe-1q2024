#ifndef _TIME_H_
#define _TIME_H_
#include <stdint.h>
void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void sleep(uint32_t ticksToWait);
#endif
