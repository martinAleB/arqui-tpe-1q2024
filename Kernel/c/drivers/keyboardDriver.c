#include <keyboardDriver.h>
#include <lib.h>
#include <videoDriver.h>

#define KEYS 58
#define MAX_PRESS_KEY 0x70 // Los valores superiores son los release de las teclas
#define TAB_NUM 4

// Define de teclas especiales:
#define ESC 0x01
#define ENTER 0x1C
#define BACKSPACE 0x0E
#define TAB 0x0F
#define L_SHIFT_PRESS 0x2A
#define L_SHIFT_RELEASE 0xAA
#define R_SHIFT_PRESS 0x36
#define R_SHIFT_RELEASE 0xB6
#define CAPS_LOCK_PRESS 0x3A

// TODO
#define CTRL_PRESS 0x1D
#define CTRL_RELEASE 0x9D
#define ALT_PRESS 0x3B
#define ALT_RELEASE 0xB8

static unsigned char keyValues[KEYS][2] = {
	{0, 0},
	{27, 27},
	{'1', '!'},
	{'2', '@'},
	{'3', '#'},
	{'4', '$'},
	{'5', '%'},
	{'6', '^'},
	{'7', '&'},
	{'8', '*'},
	{'9', '('},
	{'0', ')'},
	{'-', '_'},
	{'=', '+'},
	{8, 8},
	{9, 9},
	{'q', 'Q'},
	{'w', 'W'},
	{'e', 'E'},
	{'r', 'R'},
	{'t', 'T'},
	{'y', 'Y'},
	{'u', 'U'},
	{'i', 'I'},
	{'o', 'O'},
	{'p', 'P'},
	{'[', '{'},
	{']', '}'},
	{13, 13},
	{0, 0},
	{'a', 'A'},
	{'s', 'S'},
	{'d', 'D'},
	{'f', 'F'},
	{'g', 'G'},
	{'h', 'H'},
	{'j', 'J'},
	{'k', 'K'},
	{'l', 'L'},
	{';', ':'},
	{39, 34},
	{'`', '~'},
	{0, 0},
	{'\\', '|'},
	{'z', 'Z'},
	{'x', 'X'},
	{'c', 'C'},
	{'v', 'V'},
	{'b', 'B'},
	{'n', 'N'},
	{'m', 'M'},
	{',', '<'},
	{'.', '>'},
	{'/', '?'},
	{0, 0},
	{0, 0},
	{0, 0},
	{' ', ' '},
};

// POR AHORA F1, ..., F12 no hacen nada.
char isFKey(unsigned int key)
{
	return (key >= 0x3B && key <= 0x44) || key == 0x57 || key == 0x58;
}

char isSpecialKey(unsigned int key)
{
	return key == ESC || key == ENTER || key == BACKSPACE ||
		   key == L_SHIFT_PRESS || key == R_SHIFT_PRESS ||
		   key == CAPS_LOCK_PRESS || key == TAB ||
		   isFKey(key);
}

void getKey()
{

	unsigned int key;
	int shift = 0;
	int capsLock = 0;

	key = getKeyPressed();

	switch (key)
	{
	case R_SHIFT_PRESS:
	case L_SHIFT_PRESS:
		shift = 1;
		break;
	case R_SHIFT_RELEASE:
	case L_SHIFT_RELEASE:
		shift = 0;
		break;
	case CAPS_LOCK_PRESS:
		capsLock = (capsLock + 1) % 2;
		break;
	case BACKSPACE:
		vdDelete();
		break;
	case ENTER:
		vdNewline();
		break;
	case TAB:
		for (int i = 0; i < TAB_NUM; i++)
			vdPrintChar(' ');
		break;
	}

	int shifted = shift;
	
	if (key < MAX_PRESS_KEY)
	{
		if (!isSpecialKey(key))
		{
			if (keyValues[key][0] >= 'a' && keyValues[key][0] <= 'z')
			{
				if (capsLock == 1)
					shifted = shifted ? 0 : 1;
			}
			vdPrintChar(keyValues[key][shifted]);
		}
	}
}

uint64_t readBuffer(char *buffer, uint64_t count)
{
	uint16_t key;
	uint8_t shift = 0;
	uint8_t capsLock = 0;
	uint8_t isEnter = 0;
	uint64_t it = 0;
	while (!isEnter)
	{
		key = getKeyPressed();
		switch (key)
		{
		case R_SHIFT_PRESS:
		case L_SHIFT_PRESS:
			shift = 1;
			break;
		case R_SHIFT_RELEASE:
		case L_SHIFT_RELEASE:
			shift = 0;
			break;
		case CAPS_LOCK_PRESS:
			capsLock = (capsLock + 1) % 2;
			break;
		case BACKSPACE:
			if (it > 0)
			{
				it--;
				vdDelete();
			}
			break;
		case ENTER:
			vdNewline();
			isEnter = 1;
			break;
		case TAB:
			for (int i = 0; i < TAB_NUM; i++)
			{
				vdPrintChar(' ');
				if (it < count)
					buffer[it++] = ' ';
			}
			break;
		}

		int shifted = shift;

		if (key < MAX_PRESS_KEY)
		{
			if (!isSpecialKey(key))
			{
				if (keyValues[key][0] >= 'a' && keyValues[key][0] <= 'z')
				{
					if (capsLock == 1)
						shifted = shifted ? 0 : 1;
				}
				vdPrintChar(keyValues[key][shifted]);
				if (it < count)
					buffer[it++] = keyValues[key][shifted];
			}
		}
	}
	return it;
}
