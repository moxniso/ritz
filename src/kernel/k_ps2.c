#include <kernel/kcore.h>
#include <graphics/keymap.h>

void rk_initkb(void)
{
    rk_writeport(0x21, 0xFD); // Enable IRQ1 only
}

// TODO: rk_ledset

char rk_getchar(void)
{
   char key = -1;
   while (1) {
     if (rk_readport(0x64) & 0x01) {
          key = rk_readport(0x60);
          if (key > 0)
              return keymap[key];
     }
   }
}

