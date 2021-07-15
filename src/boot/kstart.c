#include <kernel/kcore.h>
#include <graphics/display.h>
#include <string.h>
#include <kmode.h>

#define kstring "ritz kernel | compiled on " __DATE__ " at " __TIME__
#define kcredit "(c) 2021 moxniso"

BOOL rstflag;
extern char* ritztan;

void rkmain()
{
        init_idt();
        rk_disablepics();

        rk_gfxmode(FALSE);
	rk_clearvmem();
	rk_hidecursor();
	rkmode_init();

	short pos = rk_repos(cpos(20, 5));
	rk_print(kstring, pos);
	rk_handlenewline(&pos);
	rk_print(kcredit, pos + (strnlen(kstring, VGA_WIDTH) / 2));
	
	*promptpos = START_POS;
	rk_newprompt();

	for (int i = (VGA_WIDTH*2); i < ((VGA_WIDTH*2)*2) ;i++) 
		rk_drawhash(i, 0x04);

	rkmode_open(FALSE);	
	rk_kill();
}




