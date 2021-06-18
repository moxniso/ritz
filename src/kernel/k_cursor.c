#include <kernel/kcore.h>
#include <graphics/display.h>

short rk_handlenewline(short* pos)
{
    if ((*pos + (VGA_WIDTH*2)) & 0x1) *pos += ((VGA_WIDTH*2)+1); // if it's odd (in an attribute byte)
    else *pos += (VGA_WIDTH*2); // if it's even

    rk_repos(*pos);
    ypos++;
    return *pos;
}

void rk_newprompt(void)
{
    rk_print("A:\\>", rk_handlenewline(promptpos));
}
