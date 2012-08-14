/*
** idt.c for  in /home/mk/kernel_svn/duc_l_mk
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Sat Feb 14 18:42:46 2009 Mortal Kernel
** Last update Wed Jul  8 22:12:57 2009 Duc Lionel
*/

#include "interrupts.h"
#include "libkern.h"
#include "isrs.h"


t_idt_entry	idt[256];
t_idt_ptr	idt_ptr;

static void	create_idt_entry(int n, void (*base_handler)(), u16 selector, u8 flags)
{
  u32	base;

  base = (u32)base_handler;
  idt[n].base_low = base & 0xFFFF;
  idt[n].base_high = (base >> 16) & 0xFFFF;
  idt[n].null_byte = 0;
  idt[n].flags = flags;
  idt[n].selector = selector;
}

void	create_idt()
{
  int	i;

  idt_ptr.limit = sizeof(t_idt_entry) * 256 - 1;
  //idt_ptr.limit = sizeof(idt);
  idt_ptr.base = 0x800; //juste pour etre sur qu'elle soit bien la ou elle doit
  kmemset(idt, 0, sizeof(*idt) * 256);
  i = 0;
  while (i < 256)
    {
      create_idt_entry(i, isrs_tab[i].handler, 0x08, 0x8E);
      i++;
    }
  create_idt_entry(0x80, isrs_tab[0x80].handler, 0x08, 0xEE);
  kmemcpy((void*)idt_ptr.base, &idt, idt_ptr.limit);
  asm("lidtl (idt_ptr)");
}
