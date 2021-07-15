[bits 32]

global _start32
global ritztan
extern rkmain
extern rk_kill

section .text

; GRUB header
align 4
dd 0x1badb002
dd 00
dd - (0x1badb002 + 0x00)

ritztan: incbin "boot/ritztan.bin"

_start32:
	cli
	mov esp, stack
	call rkmain ; off we go!
	jmp rk_kill

section .bss
align 32
resb 20000 ; 20 KB
stack: