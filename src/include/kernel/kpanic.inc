global phandle0
global phandle1
global phandle2
global phandle3
global phandle4
global phandle5
global phandle6
global phandle7
global phandle8
global phandle9
global phandle10
global phandle11
global phandle12
global phandle13
global phandle14
global phandle15
global phandle16
global phandle17
global phandle18

extern rkpanic

%macro set 1
	cli
	push %1
	jmp rkpanic
%endmacro

phandle0: set 0 ; Division by zero
phandle1: set 1 ; Debug exception
phandle2: set 2 ; Non-maskable interrupt
phandle3: set 3 ; Breakpoint exception
phandle4: set 4 ; Detected overflow
phandle5: set 5 ; Out of bounds
phandle6: set 6 ; Invalid opcode
phandle7: set 7 ; No co-processor
phandle8: set 8 ; Double fault
phandle9: set 9 ; Co-processor segment overrun
phandle10: set 10 ; Bad TSS
phandle11: set 11 ; Segment not present
phandle12: set 12 ; Stack fault
phandle13: set 13 ; General protection fault
phandle14: set 14 ; Page fault
phandle15: set 15 ; Unknown interrupt
phandle16: set 16 ; Coprocessor fault
phandle17: set 17 ; Alignment check exception
phandle18: set 18 ; Machine check exception




