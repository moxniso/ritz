[bits 16]
section .text

SCREENSIZE equ 4000
errmsg: db "FATAL ERROR", 0

ferror:
	mov ah, 0bh
	xor bh, bh
	mov bl, 4
	int 10h

	mov si, errmsg
	call putstr
	cli
	hlt

putstr:
	mov ah, 0x0e		
	pusha
	.loop:
		mov al, [si]
		cmp al, 0
		jnz .print_char
		popa	
		ret
		
	.print_char:
		int 10h
		add si, 1
		jmp .loop	

sleep:	
          mov ah, 86h
          xor al, al
          int 15h
	  ret	
	
get_cursor_pos:
	  mov ah, 03h
	  int 10h
	  ret

set_cursor_pos:
	  mov ah, 02h
	  int 10h
          ret
	
progressbar:  	;; dl = column, dh = row
	   mov ah, 02h
	   int 10h

	   mov ah, 0eh
	   mov al, 0x5b ; [
	   int 10h

           mov bl, dl
	   add bl, 55

	   .loop:
		call sleep
	        mov ah, 0eh
		mov al, 0x23 ; #
	        int 10h

		call get_cursor_pos		
		cmp dl, bl
		jge .done
		jl .loop

	   .done:
		mov al, 0x5D ; ]
		mov ah, 0eh
	        int 10h
		ret
				
	    	  
clearscrn:
        mov ah, 03h
        push dx  ; save cursor pos

        xor dx, dx   ; set cursor pos to 0
        int 10h     

        mov ah, 0Eh  ; teletype output
        mov al, ' '
        mov cx, SCREENSIZE 
        .loop:
              int 10h
              loop .loop
              
              pop dx  ; restore cursor pos
              int 10h
              ret	    

beep:
	mov al, 0xb6
	out 43h, al

	mov ax, 1193
	out 42h, al
	mov al, ah
	out 42h, al

	or al, 00000011b
	out 61h, al

	call sleep

mute:
	xor al, al
	out 61h, al

