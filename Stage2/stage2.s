;***********************************************;
; Stage 2: stage2.asm				;
; - GDT						;
; - Go into protected mode			;
; - Activate a20				;
; - Load the kernel				;
;***********************************************;
	;; Directives for NASM ;;
	bits 	16
	org	0x1000
	jmp	main

	;; ******************** ;;
	;;     Install GDT      ;;
	;; ******************** ;;
installGDT:
	cli			; clear interrupts
	pusha			; save registers
	lgdt 	[toc]		; load GDT into GDTR
	sti			; enable interrupts
	popa			; restore registers
	ret

	;; Load Global Descriptor Table
gdt_data:
	;; First Descriptor is not used and thefore is null: (8 bytes), at offset (0x00)
	dw 0			; (32 bits = 4 bytes)
	dw 0			; (32 bits = 4 bytes)
	dw 0
	dw 0

	;; The Code descriptor: (8 bytes), at offset (0x08)
	dw 0FFFFh		; limit low (16 bits - 2 bytes)
	dw 0			; base low (16 bits - 2 bytes)
	db 0			; base middle (8 bits - 1 byte)
	db 10011011b		; access (8 bits - 1 byte)
	db 11011111b		; granularity (8 bits - 1 byte)
	db 0			; base high (8 bits - 1 byte)

	;; The Data descriptor: (8 bytes), at offset (0x10)
	dw 0FFFFh		; limit low
	dw 0			; base low
	db 0			; base middle
	db 10010011b		; access
	db 11011111b		; granularity
	db 0			; base high

end_of_gdt:
toc:
	dw end_of_gdt - gdt_data - 1 ; limit (Size of GDT) -> gdt_data is the beginning of our GDT, and end_of_gdt is the end of our GDT.
	dd gdt_data		     ; base of GDT

	;; *********************** ;;

	;; Data Section ;;
Msg	db	"[Stage 2] Preparing to load operating system...",13,10,0
Msg2	db	"[Stage 2] GDT Table loaded...",13,10,0
	;; ************ ;;

%include "puts16.s"

main:
	cli
	xor	ax, ax		; null segments
	xor	ax, ax
	mov	ds, ax
	mov	es, ax
	mov	ax, 0x9000
	mov	ss, ax		; Stack Segment now contains 0x9000
	mov	sp, 0xFFFF	; Top of stack begins at 0xFFFF and grows till 0x9000
	sti

	mov	si, Msg
	call	puts16		; Show a message

read_disk:
	mov ah, 0	; Reset drive command
	int 13h		; Call interrupt 13h
	or ah, ah	; Check for error code
	jnz read_disk	; Try again if error

	mov ax, 0x200
	mov es, ax
	mov bx, 0x0	; Destination address = 0000:2000
	mov ah, 02h	; Read sector command
	mov al, 16	; Number of sectors to read
	mov dl, 0	; Load boot disk
	mov ch, 0	; Cylinder = 0
	mov cl, 3	; Starting Sector = 3
	mov dh, 0	; Head = 0
	int 13h		; Call interrupt 13h
	or ah, ah	; Check for error code
	jnz read_disk	; Try again if error

	mov ax, 0x400
	mov es, ax
	mov bx, 0x0  	; Destination address = 0000:4000
	mov ah, 02h	; Read sector command
	mov al, 18	; Number of sectors to read (0x12 = 18 sectors)
	mov dl, 0	; Load boot disk
	mov ch, 0	; Cylinder = 0
	mov cl, 1	; Starting Sector = 1
	mov dh, 1	; Head = 1
	int 13h		; Call interrupt 13h
	or ah, ah	; Check for error code
	jnz read_disk	; Try again if error

	mov ax, 0x600
	mov es, ax
	mov bx, 0x400	; Destination address = 0000:6400
	mov ah, 02h	; Read sector command
	mov al, 18	; Number of sectors to read (0x12 = 18 sectors)
	mov dl, 0	; Load boot disk
	mov ch, 1	; Cylinder = 1
	mov cl, 1	; Starting Sector = 1
	mov dh, 0	; Head = 0
	int 13h		; Call interrupt 13h
	or ah, ah	; Check for error code
	jnz read_disk	; Try again if error

	mov ax, 0x800
	mov es, ax
	mov bx, 0x800  	; Destination address = 0000:8800
	mov ah, 02h	; Read sector command
	mov al, 18	; Number of sectors to read (0x12 = 18 sectors)
	mov dl, 0	; Load boot disk
	mov ch, 1	; Cylinder = 1
	mov cl, 1	; Starting Sector = 1
	mov dh, 1	; Head = 1
	int 13h		; Call interrupt 13h
	or ah, ah	; Check for error code
	jnz read_disk	; Try again if error

	mov ax, 0x1100
	mov es, ax
	mov bx, 0x200  	; Destination address = 0000:8800
	mov ah, 02h	; Read sector command
	mov al, 18	; Number of sectors to read (0x12 = 18 sectors)
	mov dl, 0	; Load boot disk
	mov ch, 2	; Cylinder = 1
	mov cl, 1	; Starting Sector = 1
	mov dh, 0	; Head = 1
	int 13h		; Call interrupt 13h
	or ah, ah	; Check for error code
	jnz read_disk	; Try again if error

	call	installGDT	; Load the GDT

	mov	si, Msg2
	call	puts16		; Show a message

	cli			 ; disable interrupts before entering protected mode
	mov	eax, cr0 	; set bit 0 in CR0 - go to pmode
	or	eax, 1
	mov	cr0, eax
	jmp	Stage3

	;; Stage 3 - We are in PMode! ;;

Stage3:
	;; Set Registers ;;
	mov		ax, 0x10 	; set data segments to data selector (0x10)
	mov		ds, ax
	mov		ss, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov		esp, 0x9F000 	; stack begins from 0x90000

	mov		al, 2			; set bit 2 (enable a20)
	out		0x92, al

	jmp 		0x08:0x2000
	hlt

	TIMES	512 - ($ - $$) DB 0

