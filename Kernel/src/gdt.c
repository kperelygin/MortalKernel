/*
** gdt.c for mk in /home/mk/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Fri Feb  6 02:26:18 2009 Mortal Kernel
** Last update Fri Jul 10 02:27:50 2009 Mortal Kernel
*/

#include "gdt.h"
#include "task.h"
#include "libkern.h"

t_gdt_entry	gdt[MAX_DESCRIPTORS];
t_gdt_ptr	gdt_ptr;
t_tss		ktss;

static void	gdt_set_descriptor(u32 n, u32 base, u32 limit, u8 access, u8 gran)
{
  gdt[n].base_low    = (base & 0xFFFF);
  gdt[n].base_middle = (base >> 16) & 0xFF;
  gdt[n].base_high   = (base >> 24) & 0xFF;
  gdt[n].limit_low   = (limit & 0xFFFF);
  gdt[n].granularity = (limit >> 16) & 0x0F;
  gdt[n].granularity |= gran & 0xF0;
  gdt[n].access      = access;
}

void	load_default_tss()
{
  u32	base;
  u32	limit;

  base = (u32)&ktss;
  limit = base + sizeof(ktss);
  gdt_set_descriptor(5, base, limit, 0xE9, 0x00);
  kmemset(&ktss, 0, sizeof(ktss));
  ktss.ldt = 0;
  ktss.esp0 = KESP;
  ktss.ss0 = 0x10;
  ktss.trap = 0x00;
  ktss.iomap_base = 0x00;
}

void	create_gdt()
{
  gdt_ptr.limit = sizeof(t_gdt_entry) * MAX_DESCRIPTORS - 1;
  gdt_ptr.base = (u32)&gdt;

  kmemset(gdt, 0, sizeof(gdt));
  //Null Segment
  gdt_set_descriptor(0, 0, 0, 0, 0);
  //Code Segment
  gdt_set_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  //Data Segment
  gdt_set_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  //User mode Code Segment
  gdt_set_descriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  //User mode Data Segment
  gdt_set_descriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
  //TSS
  load_default_tss();

  gdt_flush((u32)&gdt_ptr);
  tss_flush();
}
