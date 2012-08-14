.intel_syntax noprefix
.global deactivate_paging
deactivate_paging:
	mov edx, cr0
	and edx, 0x7fffffff
	mov cr0, edx
	ret
.att_syntax
