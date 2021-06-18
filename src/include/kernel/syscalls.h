#ifndef SYSCALLS_H
#define SYSCALLS_H

#define RSYS_RST 0
#define RSYS_HALT 1
#define RSYS_FOPEN 2
#define RSYS_FCLOSE 3
#define RSYS_DATE 4
#define RSYS_DATESTRS 5

#define RGFX_CLS 11
#define RGFX_DRAW 12
#define RGFX_PTC 13
#define RGFX_DC 14
#define RGFX_NCUR 15
#define RGFX_ACUR 16
#define RGFX_RPRINT 17
#define RGFX_STATUS 18
#define RGFX_REPOS 19
#define RGFX_NPRO 20
#define RGFX_ABSREPOS 21

#define RAUD_BEEP 22
#define RAUD_MUTE 23

#define RIO_GTC 31
#define RIO_LINEFEED 32

#endif /* SYSCALLS_H */
