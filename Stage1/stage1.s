;;; STAGE 1
;;; - Load Stage2 at 0x1000

	bits	16
	org	0x7C00

	jmp	start		

%include "puts16.s"

start:	

	mov	si, boot_string	
	call	puts16

	mov	ax, 0x8000
	mov	ss, ax
	mov	sp, 0xf000	; definition de la pile
	
	xor	ax, ax
	int	0x13		; resetfloppy

	mov	ax, 0x100
	mov	es, ax
	mov	bx, 0		; On met ES:BX a 0x100:0 (0x1000) l'endroit ou on va mettre le kernel
	mov	ah, 2		; opt 2 pour read
	mov	al, 1		; nb de secteur a lire
	mov	ch, 0		; track 0
	mov	cl, 2		; sector 2
	mov	dh, 0		; tete 0
	mov	dl, 0		; drive 0 (disquette)
	int	0x13		

	jc	.FAIL
	.SUCCESS:
	mov 	si, msgSUCCESS_READ
	call	puts16
	jmp	0x100:0		; jump ou on a lu
	hlt
	.FAIL:
	mov 	si, msgFAIL_READ
	call	puts16
	hlt

boot_string:		db "[BootLoader] : Starting ...", 13, 10, 0
msgSUCCESS_READ:	db "[BootLoader] : Read Kernel SUCCESS !", 13, 10, 0
msgFAIL_READ:		db "[BootLoader] : Read Kernel FAIL !", 13, 10, 0

	
	TIMES	510 - ($ - $$) DB 0
	DW	0xAA55		
	