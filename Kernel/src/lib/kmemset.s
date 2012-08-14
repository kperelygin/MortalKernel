	.file	"kmemset.s"
	.text
	.p2align 2,,3
.globl kmemset
	.type	kmemset, @function

kmemset:
	// todo: as eax is 4B, eax should be equal to the n value 4 times
	push	%edi
	push	%ecx
	movl	16(%esp), %eax	/*eax -> int n*/
	movl	12(%esp), %edi	/*string in edi*/
	movl	20(%esp), %ecx	/*length in cx*/
	cld
	repne stosb		/*while cx != 0, edi[cx] = eax*/
	pop	%ecx
	pop	%edi
	mov	%edi, %eax
	ret

