#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ritzsys.h>
#include <common.h>
#include <kmode.h>

// TODO: replace datestrs once i add a ritzsys abstraction
// and fix the inline asm for linefeed and gtc
#include <graphics/display.h> // promptpos
#include <kernel/kcore.h> // rk_datestrs and rk_handlenewline

char* kcmds_strns[RKMODE_CMDS_NUM+1];
void (*kcmds[RKMODE_CMDS_NUM+1])();
extern void rkmode_beep();
extern void cpuinfo();
BOOL msgflag;

void rkmode_open(BOOL once)
{
    char cmd[10];
    char key = 0;

    while(1) {
loop:
          rprint("               ", 0); // Clear out status msg
noclear:          
          memset(cmd, 0, RKMODE_CMDS_MAXLEN);

          for (int i=0;i<=9;i++) {
             key = rk_getchar();
             switch (key) {
                case '\n':
                    cmd[i] = '\0';
                    if (rkmode_parse(cmd) == -1) {
                          npro();
                          goto noclear; // TODO: msgflag
                    }
                    else 
                          goto loop;
                    
                case '\b':
                    delchar();
                    cmd[i-1] = '\0';
                    i -= 2;
                    break;
                default:
                    putchar(key);
                    cmd[i] = key;
                    break;
              }
          }

          for (int j=0;j<=9;j++) delchar(); // This line is only executed when the user exceeds the 10-char limit
          if (once == TRUE) break;
    }
}

int rkmode_parse(char* cmd)
{
    if (cmd[0] == '\0') return -1;
    for (int i=0;i<=RKMODE_CMDS_NUM;i++) {
        if (strncmp(cmd, kcmds_strns[i], RKMODE_CMDS_MAXLEN) == TRUE) {
            kcmds[i]();
            return i;
        }
    }

    status("Invalid command");
    return -1;
}

void date(void)
{
   time_strs ts = rk_datestrs();
   
   rprint(ts.month, rk_handlenewline(promptpos));
   absrepos((*promptpos)+(strnlen(ts.month, 10)*2));
   putchar(' ');
   putchar(ts.day_first_digit);
   putchar(ts.day_second_digit);
   npro();
}

void vendor_show(int ebx, int ecx, int edx)
{
    char name_buffer[13];
    
    name_buffer[0] = (char)ebx;
    name_buffer[1] = (char)(ebx >> 8);
    name_buffer[2] = (char)(ebx >> 16);
    name_buffer[3] = (char)(ebx >> 24);

    name_buffer[4] = (char)edx;
    name_buffer[5] = (char)(edx >> 8);
    name_buffer[6] = (char)(edx >> 16);
    name_buffer[7] = (char)(edx >> 24);
    
    name_buffer[8] = (char)ecx;
    name_buffer[9] = (char)(ecx >> 8);
    name_buffer[10] = (char)(ecx >> 16);
    name_buffer[11] = (char)(ecx >> 24);
    name_buffer[12] = '\0';
    
    rprint(name_buffer, rk_handlenewline(promptpos));
    npro();
}

int rkmode_init(void)
{
    kcmds_strns[0] = "cls";
    kcmds[0] = cls;
    
    kcmds_strns[1] = "rst";
    kcmds[1] = rst;
    
    kcmds_strns[2] = "halt";
    kcmds[2] = halt;

    kcmds_strns[3] = "beep";
    kcmds[3] = rkmode_beep;
    
    kcmds_strns[4] = "mute";
    kcmds[4] = mute;

    kcmds_strns[5] = "date";
    kcmds[5] = date;

    kcmds_strns[6] = "cpuinfo";
    kcmds[6] = cpuinfo;
}



    
        