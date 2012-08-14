.intel_syntax noprefix
.global gdt_flush
gdt_flush:
	mov eax, [esp+4]
	lgdt [eax]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
.att_syntax
	jmp $0x08, $.flush2
.intel_syntax noprefix
.flush2:
	ret

.global tss_flush
tss_flush:
	    mov ax, 0x2B
	    ltr ax
	    ret
.att_syntax
