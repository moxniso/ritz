#include <graphics/display.h>
#include <common.h>

size_t row;
size_t column;
char* vidptr = (char*)0xb8000;
unsigned int screensize = VGA_WIDTH * VGA_HEIGHT * 2;

char color = 0;
short abspos = 0;
short* promptpos = nullptr;
short xpos = 0;
short ypos = 9;
