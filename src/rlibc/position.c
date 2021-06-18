// position.c
// Misc. helper funcs for cursor positioning
// Part of rlibc
// 2021 moxniso

#include <graphics/display.h>

/* Coordinate formula:
   w = screen width
   pos = (y*w)-w+x  || pos = (y+w)-(w-x)

   Newline formula:
   pos = pos + ((w*2)-2)

   Even/odd law:
   odd + odd = even
   even + even = even
   even + odd = odd   */

short cpos(char x, char y)
{
    if (x % 2) x++;
    xpos = x;
    ypos = y;

    return (((y * VGA_WIDTH) - VGA_WIDTH) + x);
}
