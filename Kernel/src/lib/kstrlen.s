	.file	"kstrlen.s"
	.text
	.p2align 2,,3
.globl kstrlen
	.type	kstrlen, @function

kstrlen:
	push	%edi
	mov	8(%esp), %edi
	xor	%al, %al
	xor	%ecx, %ecx
	not	%ecx
	cld
	repne scasb
	not	%ecx
	dec	%ecx
	mov	%ecx, %eax
	pop	%edi
	ret
	