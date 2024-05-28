#ifndef STANDARD_LIB_H
#define STANDARD_LIB_H

#include <stdint.h>

typedef enum
{
    STDOUT = 1,
    STDERR,
    STDMARK,
} FileDescriptor;

uint64_t fdprintf(FileDescriptor fd, const char *fmt, ...);
uint64_t printf(const char *fmt, ...);
uint64_t scanf(const char *fmt, ...);
uint64_t putChar(uint64_t character);
uint8_t getChar();
uint8_t getc();
uint64_t getNextToRead(char *c);
void beep(uint32_t ticks);

#endif