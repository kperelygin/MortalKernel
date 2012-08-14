.intel_syntax noprefix
.global activate_paging
activate_paging:
	mov edx, cr0
	or edx, 0x80000000
	mov cr0, edx
	ret
.att_syntax
