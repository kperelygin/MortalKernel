#!/usr/local/bin/php
<?php
// gen_isrs.php for mk in /home/mk/duc_l_mk/Kernel/tools
// 
// Made by Mortal Kernel
// Login   <mk@epitech.net>
// 
// Started on  Sat Feb  7 16:12:52 2009 Mortal Kernel
// Last update Sat Feb  7 22:37:48 2009 Mortal Kernel
//

  //cree un fichier .s contenant les 256 'dummy' isrs
  //elles jump toutes a isr_default_func qui appelle _default_isr, une fonction
  //C contenue dans interrupts.h

$FILE = "isrs.s";
$ISRS_NAME = "_asm_isr_";//le numero de l'isr est concat ici
$cont = ".file \"$FILE\"
.text
.p2align 2,,3
.extern default_isr";

$i = 0;
while ($i < 256)
  {
    if ($i == 8 || ($i >= 10 && $i <= 14))
      {
	$isr = "
.globl	$ISRS_NAME$i
$ISRS_NAME$i:
cli
pushl	\$$i
jmp	isr_default_func

";
      }
    else
      {
	$isr = "
.globl	$ISRS_NAME$i
$ISRS_NAME$i:
cli
pushl	\$0x0
pushl	\$$i
jmp	isr_default_func

";
      }
    $cont .= $isr;
    $i++;
  }
$cont .= "isr_default_func:
pushal
push	%es
push	%ds
push	%gs
push	%fs
mov	$0x10, %ax
mov	%ax, %ds
mov	%ax, %fs
mov	%ax, %es
mov	%ax, %gs
movl	%esp, %eax
pushl	%eax
movl	\$_default_isr, %eax
call	*%eax
popl	%eax
pop	%fs
pop	%gs
pop	%ds
pop	%es
popal
addl	$8, %esp
iret
";
file_put_contents($FILE, $cont);
?>
