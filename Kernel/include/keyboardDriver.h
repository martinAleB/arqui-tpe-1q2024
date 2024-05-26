#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <naiveConsole.h>

unsigned int getKeyPressed();
void writeIntoBuffer();
unsigned char nextFromBuffer();
/* void getKey();
uint64_t readBuffer(char *buffer, uint64_t count);
 */
#endif