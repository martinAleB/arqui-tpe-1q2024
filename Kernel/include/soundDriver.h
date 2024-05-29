#ifndef _SOUND_DRIVER_H
#define _SOUND_DRIVER_H

#include <stdint.h>

uint8_t inb(uint8_t a);
void outb(uint8_t a, uint8_t b);
void beep(uint16_t hz, uint16_t ticks);

#endif