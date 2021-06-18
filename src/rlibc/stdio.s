[bits 32]

extern abspos
extern rprint

global getchar
global putchar
global delchar
global puts

getchar:
	pop edx
        mov eax, 31
        int 0x50
	mov eax, ebx
	push edx
	ret

putchar:
        mov eax, 13
	mov ebx, [esp+4]
	int 0x50
	ret

delchar:
	mov eax, 14
	int 0x50
	ret

puts:
	mov eax, [esp+4] ; str
	mov ebx, abspos
	mov ecx, [ebx]

	push ecx
	push eax
	call rprint
	
	xor eax, eax
	add esp, 8
	ret	
	