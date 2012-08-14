.intel_syntax noprefix
.global copy_frame

copy_frame:			/*void (void *dst, void *src)*/
	push	ebx		/*save ebx do be C compatible*/
	pushf			/*push flags*/
	cli			/*disable interrupts*/
	mov	edx, [esp + 12]
	mov	ebx, [esp + 16]	/*use the stack while we can*/

	/*ebx = src,  edx = dst*/

	mov	ecx, cr0	/*get the CR0*/
	and	ecx, 0x7fffffff
	mov	cr0, ecx	/*disable paging*/

	mov	ecx, 1024	/*set a counter*/

.loop:
	mov	eax, [ebx]
	mov	[edx], eax

	add	ebx, 4
	add	edx, 4		/*dst++;src++;*/
	dec	ecx		/*count--*/

	cmp	ecx, 0
	ja	.loop		/*again*/

	mov	ecx, cr0
	or	ecx, 0x80000000	/*enable paging again*/
	mov	cr0, ecx

	popf
	pop	ebx
	ret

.att_syntax
