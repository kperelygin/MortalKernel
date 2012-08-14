/*
** interrupts.c for mk in /home/mk/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Sat Feb  7 17:19:29 2009 Mortal Kernel
** Last update Sat Jul 11 00:40:28 2009 Duc Lionel
*/

#include "interrupts.h"
#include "io.h"
#include "libkern.h"
#include "timer.h"
#include "task.h"
#include "syscall.h"

t_time	_timet = 0;

void	_default_isr(t_int_frame *regs)
{
  if (regs->int_num == 32)
    clock_isr(regs);
  else if (regs->int_num == 6)
    asm volatile("hlt");
  else if (regs->int_num == 33)
    keyboard_isr(regs);
  else if (regs->int_num == PAGE_FAULT)
    page_fault(regs);
  else if (regs->int_num == GPF)
    general_prot_fault(regs);
  else if (regs->int_num == SW_INTNUM)
    handle_syscalls(regs);
  else if (regs->int_num != 39)
    kprintf("Received interruption number %d (IRQ %d) (errcode = %d)\n", regs->int_num, regs->int_num - 31, regs->err_code);
  outb(0x20, 0x20);
  outb(0xA0, 0x20);
  STI();
}

void	clock_isr(t_int_frame *regs)
{
  _timet++;
  /* _timet % 200 == 1 second on Bochs */
  //  if (_timet % 50 == 0)
  //    {
  switch_task(regs);
      //    }
}

int		keyboard_isr(__attribute__((unused))t_int_frame *regs)
{
  u32		i;
  u8		scancode;
  static u32	shift = 0;
  static u32	escaped = 0;
  u32		ret = 0;

  i = inb(0x64);
  while ((i & 0x01) == 0)
    i = inb(0x64);
  if (i == 0)
    return (0);
  scancode = inb(0x60);
  if (scancode == 0x2a || scancode == 0x36)
    {
      shift = 1;
      return (0);
    }
  else if (scancode == (0x2a + 0x80) || scancode == (0x36 + 0x80))
    {
      shift = 0;
      return (0);
    }
  if (scancode == 224)
    {
      escaped = 1;
      return (0);
    }
  if (shift && scancode - 0x80 < 0 && kb_map_shift[scancode] != 0xFF)
    {
      if (escaped != 1)
	ret |= (kb_map_shift[scancode]);
      else
	{
	  ret |= 224;
	  ret |= (kb_map_shift[scancode] << 8);
	}
    }
  if (!shift && scancode - 0x80 < 0 && kb_map[scancode] != 0xFF)
    {
      if (escaped != 1)
	{
	  ret = ret | kb_map[scancode];
	}
      else
	{
	  ret |= 224;
	  ret = ret | (kb_map[scancode] << 8);
	}
    }
  if (escaped == 1)
    escaped = 0;
  gl_newcode = ret;
  return (ret);
}

void	page_fault(t_int_frame *regs)
{
  u32	faulting_address;

  asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
  kprintf("Page fault at 0x%x!\n", faulting_address);
  gl_current_task->state = DELETE;
  switch_task(regs);
  kprintf("Error code = 0x%x\n", regs->err_code);
  while (1);
}

void	general_prot_fault(__attribute__((unused))t_int_frame *regs)
{
  u32	faulting_address;

  asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
  kprintf("Protection fault at 0x%x! (Reboot :/)\n", faulting_address);
  kprintf("Current task was [%s]\n", gl_current_task->name);
  while (1);
}
