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
uint64_t readLine(char buff[]);
uint64_t putChar(uint64_t character);
uint8_t getChar();
uint8_t getc();
int strcmp(char * s1, char *s2);
void toMinus(char * str);

#endif