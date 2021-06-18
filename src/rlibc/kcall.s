[bits 32]

global cls
global halt
global rst
global beep
global mute
global draw
global rprint
global npro
global absrepos
global repos
global status
global linefeed

cls:
	mov eax, 11
	jmp do_call

halt:
	mov eax, 1
	jmp do_call

rst:
	xor eax, eax
	jmp do_call

mute:
	mov eax, 23
	jmp do_call

npro:
	mov eax, 20
	jmp do_call

beep:
	mov eax, 22
	jmp setup_single

draw:
	mov eax, 12
	jmp setup_full

repos:
	mov eax, 19
	jmp setup_full

absrepos:
	mov eax, 21
	jmp setup_single

linefeed:
	mov eax, 32
	int 0x50
	mov eax, ebx
	ret

status:
	pop edx
	mov eax, 18
	mov ebx, [esp]
	int 0x50

	mov ecx, 0x50 ; delimiter of 100
	xor eax, eax ; pointer offset
	status_strnlen:
		cmp byte [ebx+eax], 0
		je end
		inc eax
		loop status_strnlen

	end:
		push edx
		ret
	
rprint:
	pop edx
	mov eax, 17
	mov ebx, [esp]
	mov ecx, [esp+4]
	int 0x50

	xor eax, eax ; returning 0
	push edx
	ret	

setup_single:
	mov ebx, [esp+4]
	jmp do_call

setup_full:
	mov ebx, [esp+4]
	mov ecx, [esp+8]
do_call:
	int 0x50
	ret
