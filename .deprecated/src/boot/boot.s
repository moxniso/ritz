;; Ritz two-stage bootloader | 16-bit real mode -> 32-bit protected mode
;; 2021 moxniso

;; File created: March 9 2020
;; Last modified: July 14 2021

[bits 16]
section .text

mov ax, cs
mov ds, ax
mov es, ax
mov ax, 0x7000
mov ss, ax
mov sp, ss

;; setup VGA
xor ax, ax
mov al, 03h
int 10h

;; use block cursor
mov ah, 01h
mov cx, 0007h
int 10h
	
;; enable A20 bit
mov ax, 0x2401
int 0x15

mov ah, 0x02 			; read sectors
mov al, 32			; number of sectors to read
xor ch, ch			; cylinder index
xor dh, dh			; head index
mov cl, 2			; sector index
xor dl, dl 			; read from "floppy"
mov bx, _start32  		; target pointer
int 13h

jc ferror ; disk read error
call ritztan_splash

; for splash screen later on
xor ax, ax
mov ah, 13h
int 10h

;; enter protected mode
cli 
lgdt [gdt_pointer]
mov eax, cr0
or al, 1
mov cr0, eax	

mov ax, DATA_SEG
mov ds, ax	
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
jmp CODE_SEG:_start32

%include "boot/gdt.inc"
%include "boot/splash.s"
%include "boot/librb.s"

times 510-($-$$) db 0
dw 0xaa55

;; boot sector ends here

section .data
title db 0x0a, "Ritz32 bootloader", 0x0a, 0
credit db "2021 moxniso", 0x0a, 0x0a, 0
loading db "Loading kernel...", 0x0a, 0

[bits 32]
section .text
extern rkmain
extern rk_clearvmem
_start32:	
	call rk_clearvmem
	mov esp, stack_space 	; give the kernel it's memory
	jmp rkmain		; and relinquish control

section .bss
align 32
resb 20000 		; 20 KB
stack_space:

	










