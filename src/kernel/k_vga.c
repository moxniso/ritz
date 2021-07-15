#include <kernel/kcore.h>
#include <graphics/vga.h>
#include <stdlib.h>

#define mod_regs(f, s, n, e) \
    for (int i=0;i < n;i++) { \
        e; \
        rk_writeport(f, i); \
        rk_writeport(s, regs[offset]); \
        offset++; \
    }
    
BOOL rk_gfxmode(BOOL set)
{
        if (set != FALSE && set != TRUE) {
            rk_statusprint("rk_mode13h: invalid set param, kernel panic", RED);
            rk_kill();
        }

        // preserve the original hardcoded regs so that
        // the switch to or from 13h can be done
        // multiple times
        unsigned char regs[VGA_NUM_REGS];
        unsigned int offset = 0;       

        if (set)
            memcpy(regs, mode_13h_regs, VGA_NUM_REGS);
        else
            memcpy(regs, mode_03h_regs, VGA_NUM_REGS);
        
        rk_writeport(VGA_MISC_WRITE, regs[offset]);
        offset++;        
        mod_regs(VGA_SEQ_INDEX, VGA_SEQ_DATA, VGA_NUM_SEQ_REGS, NULL);
        mod_regs(VGA_CRTC_INDEX, VGA_CRTC_DATA, VGA_NUM_CRTC_REGS, NULL);
        
        // unlock CRTC regs
        rk_writeport(VGA_CRTC_INDEX, 0x03);
        rk_writeport(VGA_CRTC_DATA, rk_readport(VGA_CRTC_DATA) | 0x80);
        rk_writeport(VGA_CRTC_INDEX, 0x11);
        rk_writeport(VGA_CRTC_DATA, rk_readport(VGA_CRTC_DATA) & ~0x80);
        regs[0x03] |= 0x80;
        regs[0x11] &= ~0x80; // proof jews work at VESA

        mod_regs(VGA_GC_INDEX, VGA_GC_DATA, VGA_NUM_GC_REGS, NULL);
        mod_regs(VGA_AC_INDEX, VGA_AC_WRITE, VGA_NUM_AC_REGS, rk_readport(VGA_INSTAT_READ));
        
        rk_readport(VGA_INSTAT_READ);
        rk_writeport(VGA_AC_INDEX, 0x20);
        
        return TRUE;
}


        