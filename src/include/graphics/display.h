#ifndef DISPLAY_H
#define DISPLAY_H
#include <stddef.h>

#define VGA_HEIGHT (25)
#define VGA_WIDTH (80)
#define START_POS (2242)
extern size_t row;
extern size_t column;
extern char color;
extern char* vidptr;
extern unsigned int screensize;

extern short abspos;
extern short* promptpos;
extern short xpos;
extern short ypos;

#endif /* DISPLAY_H */
