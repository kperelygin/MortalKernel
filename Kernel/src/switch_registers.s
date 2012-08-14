.intel_syntax noprefix
.global switch_registers
switch_registers:
	cli
	mov ecx, [esp + 4]
	mov ebp, [esp + 8]
	mov eax, [esp + 12]
	mov esp, [esp + 16]
	mov cr3, eax
	mov al,0x20
	out 0x20,al
	out 0xA0,al
	mov eax, 0x12345
	sti
	jmp ecx
.att_syntax
