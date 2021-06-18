#ifndef KCORE_H
#define KCORE_H

#include <kernel/kcommon.h>
#include <utils/position.h>

void rk_clearvmem();
void rk_drawhash(int pos, char color);
short rk_repos(int pos);
void rk_hidecursor(void);
void rk_showcursor(void);
void rk_initkb(void);
void rk_disablepics();
void rk_print(char* string, short pos);
void rk_putchar(char a);
char rk_getchar(void);
void rk_delchar(void);
void rk_iprint(char* string, short pos);
void rk_lolcat(char* string, char color, char limit, short pos);
void rk_statusprint(char* string, char color);
void rk_beep(int freq);
void rk_mute(void);
int rk_date(void);
time_strs rk_datestrs(void);
void rk_kill();

short rk_handlenewline(short* pos);
void rk_newprompt(void);

#endif /* KCORE_H */
