puts16:				;string in si
	lodsb
	or	al, al
	jz	.end
	mov	ah, 0x0E
	int	0x10
	jmp	puts16
	.end
	ret