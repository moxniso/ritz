;; Ritz x86 two-stage bootloader | 16-bit real mode -> 32-bit protected mode
;; written by moxniso

;; File created: March 9 2020
;; Last modified: March 27 2021

[bits 16]

;; set up the stack
mov ax, cs
mov ds, ax
mov es, ax
mov ax, 0x7000
mov ss, ax
mov sp, ss

;; set up VGA
mov ax, 0
mov al, 03h
int 10h

; Change the cursor to the block cursor
mov ah, 01h
mov cx, 0007h
int 10h
	
;; set bkg color to blue
mov ah, 0bh
mov bl, 9
int 10h

mov ah, 3
mov cl, dh

mov si, title
call putstr

mov ah, 02h
mov dh, cl
add dh, 2
mov dl, 0
int 10h

;; draw yellow line at the top
call yelsq

mov si, credit
call putstr
mov si, loading
call putstr	

; move the cursor out of sight
mov ah, 02h
mov dh, 100
mov dl, 100
int 10h
	
; call beep
; call sleep
; call mute

; move the cursor back 
mov ah, 02h
xor dh, dh
xor dl, dl	
int 10h
	
;; Enable A20 bit
mov ax, 0x2401
int 0x15

;; Read from disk
mov [disk], dl

mov ah, 0x02 			; Read sectors
mov al, 60			        ; Number of sectors to read
xor ch, ch			        ; Cylinder index
xor dh, dh			        ; Head index
mov cl, 2			        ; Sector index
mov dl, [disk] 			; Disk index
mov bx, copy_target  		; Target pointer
int 0x13

jc ferror	; Disk read error

;; change bkg color back to black
mov ah, 0bh
xor bh, bh
xor bl, bl
int 10h

      ;; Enter protected mode!
cli 				; Block interrupts
lgdt [gdt_pointer] 		; Load GDT address (Global Descriptor Table)
mov eax, cr0
or al, 1			; set Protection Enable bit in Control Register 0 (cr0)
mov cr0, eax	

mov ax, DATA_SEG
mov ds, ax	
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
jmp CODE_SEG:_start32_ritz

%include "boot/gdt.inc"
%include "boot/librb.inc"
	
title db 0x0a, "Ritz32 bootloader...", 0x0a, 0
credit db "2020 moxniso", 0x0a, 0x0a, 0
loading db "Loading kernel...", 0x0a, 0

yelsq:
	call get_cursor_pos
	push dx
	xor dx, dx
	call set_cursor_pos

	mov al, '#'
	mov cx, 80	
	mov bl, 14
	mov ah, 0x09
	int 10h

	pop dx
	call set_cursor_pos
	ret
	
times 510-($-$$) db 0
dw 0xaa55 ; magic number
	
copy_target:
[bits 32]
extern rkmain
extern rk_clearvmem
; %include "kstart.s"	
_start32_ritz:	
	call rk_clearvmem
	mov esp, stack_space 	; set stack pointer
	jmp rkmain		; relinquish control to the kernel

section .bss
align 4
resb 100000 		; 100 KB
stack_space:

	










