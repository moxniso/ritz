#include <kernel/kcore.h>

BOOL beepflag = FALSE;

void rk_mute(void)
{
    rk_writeport(0x61, (rk_readport(0x61) & 0xFC));
    // rk_writeport(0x61, (rk_readport(0x61) ^ rk_readport(0x61)));
    beepflag = FALSE;
}

void rk_beep(int freq)
{
     rk_writeport(0x43, 0xb6);
     rk_writeport(0x42, (char)freq);
     rk_writeport(0x42, ((char)freq >> 8));

     rk_writeport(0x61, rk_readport(0x61) | 3);

     beepflag = TRUE;
}
