global rk_readport
global rk_writeport
global rk_kill
global rk_disablepics

rk_readport:
	mov dx, [esp + 4]
	in al, dx ;dx is the port number and al is where the data is stored.
	ret

rk_writeport:
	mov dx, [esp + 4]
	mov al, [esp + 8]
	out dx, al
	ret

rk_disablepics:
	mov dx, 0xFF
	mov al, 0x21
	out dx, al
	mov dx, 0xA1
	out dx, al
	ret

rk_kill:
	cli
	hlt

