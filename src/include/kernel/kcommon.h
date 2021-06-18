#ifndef KCOMMON_H
#define KCOMMON_H

#include <common.h>

char rk_readport(short a);
void rk_writeport(short a, short b);
void rk_disablepics(void);
void rk_kill(void);
void init_idt(void);

#define BLACK 0x00
#define BLUE 0x01
#define GREEN 0x02
#define CYAN 0x03
#define RED 0x04
#define YELLOW 0x0E

extern BOOL beepflag;

#endif /* KCOMMON_H */
