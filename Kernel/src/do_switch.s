.intel_syntax noprefix
.global do_switch
do_switch:
	mov al,0x20
	out 0x20,al
	out 0xA0,al
	pop gs
	pop fs
	pop es
	pop ds
	pop edi
	pop esi
	pop ebp
	pop ebx
	pop edx
	pop ecx
	pop eax
	iret
.att_syntax
