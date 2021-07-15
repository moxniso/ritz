[bits 16]
section .text

vga_addr equ 0xa000
screen_size equ 64000
extern ritztan

ritztan_splash:
	pusha
	mov bx, [esp+36]
	mov ax, 13h
	int 10h

	lea si, ritztan
	lea di, vga_addr
	mov cx, screen_size
	push ds
	pop es
	cld
	rep movsb
		
	xor ax, ax
	int 16h
	mov al, 03h
	int 10h
	
	popa
	push bx
	ret
