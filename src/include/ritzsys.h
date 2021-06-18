#ifndef SYSCALL_H
#define SYSCALL_H

void cls();
void halt();
void rst();
void beep(int freq);
void mute();
void draw(int pos, char color);
int rprint(char* str, short pos);
void npro();
void repos(int x, int y);
void absrepos(int abs);
short linefeed();
int status(char* str);

#endif