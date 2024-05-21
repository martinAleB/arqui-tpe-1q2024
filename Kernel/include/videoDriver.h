#include <stdint.h>
#include <font.h>
#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

/*************************************
**
** DECLARACIONES DE CONSTANTES
**
**************************************/

#define SCREEN_WIDTH_PIXELS 1024
#define SCREEN_HEIGHT_PIXELS 768 
#define MARGIN_SIZE 1

#define SMALL_FONT 1
#define LARGE_FONT 2


/*************************************
**
** DECLARACIONES DE FUNCIONES
**
**************************************/

/* DE NAIVE CONSOLE -> TRADUCIR
 
void ncPrint(const char *string);
void ncPrintChar(char character);
uint64_t ncNPrintStyled(const char *string, uint8_t style, uint64_t N);
void ncPrintCharStyled(char character, uint8_t style);
void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();
void ncDelete();

*/

unsigned char *getCharHexData(uint8_t c);
uint8_t *getLargeCharHexData(uint8_t c);
void consolePrintString(char* s, uint8_t size, uint32_t color, uint32_t bgColor);
void clear();
void rainbowPrint(char *s);
void drawRectangle( uint32_t color, uint16_t up_l_x, uint16_t up_l_y, uint16_t lo_r_x, uint16_t lo_r_y);

#endif