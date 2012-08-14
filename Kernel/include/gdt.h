/*
** gdt.h for mk in /home/mk/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Fri Feb  6 02:33:59 2009 Mortal Kernel
** Last update Wed Jul  1 13:50:58 2009 Mortal Kernel
*/

#ifndef __GDT_H__
# define __GDT_H__

# include "ctypes.h"

/* Defines */
# define MAX_DESCRIPTORS 6

typedef struct	s_tss
{
  u32		prev_tss; // Unused -- used in hardware task switching
  u32		esp0; // stack pointer when switching to ring 0
  u32		ss0; // stack segment when switching to ring 0
  u32		esp1; // -- Unused ....
  u32		ss1;
  u32		esp2;
  u32		ss2;
  u32		cr3;
  u32		eip;
  u32		eflags;
  u32		eax;
  u32		ecx;
  u32		edx;
  u32		ebx;
  u32		esp;
  u32		ebp;
  u32		esi;
  u32		edi;
  u32		es; // segments values when switching to ring 0
  u32		cs;
  u32		ss;
  u32		ds;
  u32		fs;
  u32		gs;
  u32		ldt; // Unused
  u16		trap;
  u16		iomap_base;
}__attribute__((packed))t_tss;

/* GDT Structure */

typedef struct	s_gdt_entry
{
  u16	limit_low;           // The lower 16 bits of the limit.
  u16	base_low;            // The lower 16 bits of the base.
  u8	base_middle;         // The next 8 bits of the base.
  u8	access;              // Access flags, determine what ring (e.g. 0 or 3) this segment can be used in.
  u8	granularity;	     // Complete BS :P
  u8	base_high;           // The last 8 bits of the base.
}__attribute__((packed))t_gdt_entry;

typedef struct	s_gdt_ptr
{
  u16		limit;
  u32		base;
}__attribute__((packed))t_gdt_ptr;

extern t_gdt_entry	gdt[MAX_DESCRIPTORS];
extern t_gdt_ptr	gdt_ptr;
extern t_tss		ktss;

/* Access the ASM function from the C code. */
extern void gdt_flush(u32);
extern void tss_flush();

/* Prototypes */
void	create_gdt();

#endif /* __GDT_H__ */
