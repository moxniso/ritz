[bits 32]

global rkmode_beep
global cpuinfo
extern beep
extern vendor_show

rkmode_beep:
	push 1000
	call beep
	add esp, 4
	ret

cpuinfo:
	xor eax, eax
	cpuid
	push edx
	push ecx
	push ebx
	
	call vendor_show

	add esp, 12
	ret
