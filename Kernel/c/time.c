#include <rtc.h>
#include <stdint.h>

static unsigned long ticks = 0;
static int frequency = 18;

#define PIT_FREQ 1193182

void timer_handler()
{
	ticks++;
}

int ticks_elapsed()
{
	return ticks;
}

int seconds_elapsed()
{
	return ticks / frequency;
}
void sleep(uint32_t ticksToWait)
{
	int ticksAtCallTime = ticks_elapsed();
	while (ticks - ticksAtCallTime < ticksToWait)
		;
}
void setTickFrequency(uint16_t freq)
{
	frequency = freq;
	int ticks = PIT_FREQ / freq;
	outb(0x43, 0xb6);
	outb(0x40, (uint8_t)(ticks));
	outb(0x40, (uint8_t)(ticks >> 8));
}
