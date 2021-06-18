[bits 32]

%include "../include/kernel/kpanic.inc"

global load_idt
global kbhandle
global rk_syscall
extern syscall_handle

extern rk_kill
extern rk_iprint

load_idt:
	mov eax, [esp+4]
	lidt [eax]
	sti
	ret

rk_syscall:
	pushad ; guarantee preservation of regs after syscalls

	cmp eax, 17 ; rprint
	jne not_rprint
	
	push ecx
	push ebx
	call rk_iprint
	push eax ; keep stack frame consistent
	jmp done
	
	not_rprint:
		push ecx
		push ebx
		push eax

		call syscall_handle

	done:
	        mov al, 0x20
	        out 0x20, al ; acknowledge EOI to PICs
	        out 0xA0, al

		pop eax
		pop ebx
		pop ecx
		popad

		iretd 

; Test to see if rk_syscall preserves general regs correctly
; If bx was not preserved after a cls, do an rk_kill()
test_save:
        mov ax, 0x14
        mov bx, 0xAF
        int 0x50

        cmp bx, 0xAF
        jne rk_kill
	ret
