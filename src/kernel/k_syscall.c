#include <kernel/kcore.h>
#include <graphics/display.h>
#include <kernel/idt.h>
#include <kernel/syscalls.h>

/*
 *      Ritz system calls as of June 8th 2021
 *      int 0x50, command specified by 32-bit EAX register
 *
 *
 *      (SYSTEM & FILESYSTEM)
 *      0 - rst | Reset the kernel | rkmain()
 *      1 - halt | Halt the CPU | rk_kill()
 *      2 - fopen | Open file stream in FAT32 filesystem | TODO
 *      3 - fclose | Close file stream | TODO
 *      4 - date | Return struct containing CMOS time specifics
 *      5 - datestrs | date but represented as strings | TODO 
 *
 *      (GRAPHICS)
 *      11 - cls | Clear vmem | rk_clearvmem()
 *      12 - draw | Draw a pixel/character to vmem | rk_drawhash()
 *      13 - ptc | Teletype character output | rk_putchar()
 *      14 - dc | Delete character and regress cursor | rk_delchar()
 *      15 - ncur | Disable the text cursor | rk_hidecursor()
 *      16 - acur | Enable the text cursor | rk_showcursor()
 *      17 - rprint | Write a string to vmem | rk_iprint() | handled in idt.s
 *      18 - status | Print status message | rk_statusprint()
 *      19 - repos | Reposition the cursor with specific X and Y coords | rk_repos + cpos()
 *      20 - npro | Create a new prompt | rk_newprompt()
 *      21 - absrepos | Reposition the cursor with one absolute position | rk_repos
 *
 *      (AUDIO)
 *      22 - beep | PC speaker tone at arbitrary freq | rk_beep()
 *      23 - mute | Mute the PC speaker | rk_mute()
 *
 *      (INPUT/OUTPUT)
 *      31 - gtc | Get character input and return it in bx | rk_getchar()
 *      32 - linefeed | Bump the cursor directly to the next line | rk_handlenewline()
 */

extern void rkmain();

void syscall_handle(int eax, int ebx, int ecx)
{
    switch (eax) {
        case RSYS_RST: 
            rk_statusprint("Resetting...", CYAN);
            rkmain();
            break;
        case RSYS_HALT:
            rk_statusprint("CPU has been halted!", RED);
            rk_kill();
            break;
        case RGFX_REPOS:
            rk_repos(cpos(ebx, ecx));
            break;
        case RGFX_ABSREPOS:
            rk_repos(ebx);
            break;
        case RGFX_DRAW:
            rk_drawhash(ebx, (char)ecx);
            break;
        case RGFX_CLS:
            rk_clearvmem();
            *promptpos = 0;
            rk_newprompt();
            break;
        case RAUD_BEEP:
            rk_beep(1193180 / ebx);
            rk_newprompt();
            break;
        case RAUD_MUTE:
            rk_mute();
            rk_newprompt();
            break;
        case RGFX_NCUR:
            rk_hidecursor();
            break;
        case RGFX_ACUR:
            rk_showcursor();
            break;
        case RGFX_NPRO:
            rk_newprompt();
            break;
        case RGFX_PTC:
            rk_putchar((char)ebx);
            break;
        case RIO_LINEFEED: {
            short newpos = rk_handlenewline(promptpos);
            asm volatile(
                "movw %0, %%bx"
                :"=r"(newpos));
            break;
        }
        case RIO_GTC: {
            char press = rk_getchar();
            asm volatile(  // TODO: fix this bc fuck GNU
                "movb %0, %%bh"
                :"=r"(press));
            break;
        }
        case RGFX_DC:
            rk_delchar();
            break;
        case RGFX_STATUS:
            rk_statusprint((char*)ebx, CYAN);
            break;
        default:
            rk_statusprint("Invalid interrupt!", RED);
            break;
    }
}

  
