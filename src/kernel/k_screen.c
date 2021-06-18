#include <kernel/kcore.h>
#include <graphics/display.h>
#include <string.h>

void rk_clearvmem()
{
        for (int i = 0;i < screensize;i+=2) {
                vidptr[i] = ' ';
                vidptr[i+1] = 0x07;
        }
}

short rk_repos(int pos)
{
     rk_writeport(0x3D4, 0x0F);
     rk_writeport(0x3D5, (pos & 0xFF));
     rk_writeport(0x3D4, 0x0E);
     rk_writeport(0x3D5, ((pos >> 8) & 0xFF));

     abspos = pos;
     return pos;
}

void rk_hidecursor(void)
{
    rk_writeport(0x3D4, 0x0A);
    rk_writeport(0x3D5, 0x20);
}

void rk_showcursor(void)
{
    rk_writeport(0x3D4, 0x0A);
    rk_writeport(0x3D5, (rk_readport(0x3D5) & 0xC0));

    rk_writeport(0x3D4, 0x0B);
    rk_writeport(0x3D5, (rk_readport(0x3D5) & 0xE0));
}

void rk_drawhash(int pos, char color)
{
   if ((pos % 2) != 0) {
      vidptr[pos-0x1] = '#';
      vidptr[pos] = color;
   }
   else {
      vidptr[pos] = '#';
      vidptr[pos+0x1] = color;
   }
}

void rk_putchar(char a)
{
   vidptr[abspos] = a;
   vidptr[abspos+1] = color;
   color++;
   if (color >= 0x10)
           color = 0x01;

   rk_repos(abspos+2);
   xpos++;
}

void rk_delchar(void)
{
   rk_repos(abspos-2);
   vidptr[abspos] = 0;
   xpos--;
}

void rk_statusprint(char* string, char color)
{
   short p = 0;
   for (int i=0;i<=(strlen(string)+1);i++) {
     switch (string[i]) {
         case '\n':
           rk_handlenewline(&p);
           break;
         case '\0':
           return;
         default:
           vidptr[p] = string[i];
           vidptr[p+1] = color;
           p += 2;
           break;
     }
   }
}

void rk_print(char* string, short pos)
{
   short p = pos;
   for (int i=0;i<=(strlen(string)+1);i++) {
     switch (string[i]) {
         case '\n':
           rk_handlenewline(&p);
           break;
         case '\0':
           rk_repos(p);
           return;
         default:
           vidptr[p] = string[i];
           vidptr[p+1] = 0x03;
           p += 2;
           break;
     }
   }
   rk_repos(p);
}

void rk_iprint(char* string, short pos)
{
   short tmp = abspos;
   rk_print(string, pos);
   rk_repos(tmp);
}

void rk_lolcat(char* string, char color, char limit, short pos)
{
   char st_color = color;
   short p = pos;

   rk_print(string, pos);
   p++; // so it becomes odd (attribute bytes)

   for (int i=0;i<=(strnlen(string, 50)+1);i++) {
     switch (string[i]) {
         case '\n':
           rk_handlenewline(&p);
           break;
         case '\0':
           return;
         default:
           vidptr[p] = color;
           color++;
           if (color >= limit)
                color = st_color;
           p += 2;
     }
   }
}

