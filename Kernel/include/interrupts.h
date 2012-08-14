/*
** interrupts.h for mk in /home/mk/duc_l_mk/Kernel/include
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Sat Feb  7 14:57:56 2009 Mortal Kernel
** Last update Thu Jul  9 04:10:02 2009 Duc Lionel
*/

#ifndef __INTERRUPTS_H__
# define __INTERRUPTS_H__

/*IDT stuff*/

# include "ctypes.h"

typedef struct	s_idt_entry
{
  u16		base_low;
  u16		selector;
  u8		null_byte;
  u8		flags;
  u16		base_high;
}__attribute__((packed))t_idt_entry;

typedef struct	s_idt_ptr
{
  u16		limit;
  u32		base;
}__attribute__((packed))t_idt_ptr;

/*
** Cette structure definit les parametres
** que prennent les interruptions
*/
typedef struct	s_interrupt_frame
{
  u32		gs, fs, es, ds;				/* segments sauvegardes */
  u32		edi, esi, ebp, esp, ebx, edx, ecx, eax; /* de 'pushal' */
  u32		int_num, err_code;			/* push des params depuis les ISR */
  u32		eip, cs, eflags, useresp, ss;		/* push par "call" */ 
}		t_int_frame;

enum	e_exceptions
  {
    ZERO_DIV = 0,
    SS = 1, /*DEBUG*/
    NMI = 2, /*Non maskable interrupt*/
    BP = 3, /*DEBUG*/
    OVERFLOW = 4,
    BOUNDS_CHECK = 5,
    UNDEFINED_OPCODE = 6,
    NO_COPROCESSOR = 7,
    DOUBLE_FAULT = 8,
    COPROCESSOR_SEG_OVERRUN = 9,
    INVAL_TSS = 10,
    NO_SEGMENT = 11,
    STACK_SEG_OVERRUN = 12,
    GPF = 13, /*General Protection Fault*/
    PAGE_FAULT = 14,
    UNUSED = 15,
    COPROCESSOR_ERROR = 16,
    ALIGN_CHECK = 17,
    MACH_CHECK = 18
  };


/* keyboard vars */
extern int gl_newcode;
extern u32 kb_map[102];
extern u8 kb_map_shift[102];
extern u8 kb_map_escaped[102];

extern t_idt_entry	idt[256];
extern t_idt_ptr	idt_ptr;



void	create_idt();
void	reload_pic();
void	init_pit(int frequency);

/*
** Prototypes des interruptions
*/

void	_default_isr(t_int_frame *regs);
void	clock_isr(t_int_frame *regs);
int	keyboard_isr(t_int_frame *regs);
void	page_fault(t_int_frame *regs);
void	general_prot_fault(t_int_frame *regs);
void	handle_syscalls(t_int_frame *regs);

#endif
