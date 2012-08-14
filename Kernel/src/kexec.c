/*
** kexec.c for mortal kernel in /home/mk/duc_l_mk
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Tue Jun 30 00:52:36 2009 Mortal Kernel
** Last update Fri Jul 10 22:10:42 2009 Duc Lionel
*/

#include "screen.h"
#include "vmem.h"
#include "phy_mem.h"
#include "libkern.h"
#include "task.h"
#include "malloc.h"
#include "fs.h"
#include "elf.h"

static void	*allocate_place(u32 size)
{
  u32		pnum;
  void		*place;

  pnum = (size / PAGE_SIZE);
  if ((size % PAGE_SIZE) != 0)
    pnum += 1;
  place = page_alloc(gl_current_task->page_dir, pnum, PTE_RW | PTE_USER, 0);
  return (place);
}

int		kexec(t_node *file)
{
  void		*stack;
  void		*code;

  asm volatile("cli");

  /* Free the old memory */
  if (gl_current_task->brk)
    dt_memory((void *)USTACK_START, gl_current_task->brk, gl_current_task->page_dir);

  stack = allocate_place(USTACK_SIZE);
  kmemset(stack, 0, USTACK_SIZE);
  if ((code = load_elf(file)) == NULL)
    return (0);
  /* Init registers */
  kmemcpy(gl_current_task->name, file->filename, kstrlen(file->filename));
  kmemset(&gl_current_task->regs, 0, sizeof(gl_current_task->regs));
  gl_current_task->regs.cs = 0x1B;
  gl_current_task->regs.ss = 0x23;
  gl_current_task->regs.ds = 0x23;
  gl_current_task->regs.es = 0x23;
  gl_current_task->regs.fs = 0x23;
  gl_current_task->regs.gs = 0x23;
  gl_current_task->regs.esp = UESP;
  gl_current_task->regs.ebp = 0;
  gl_current_task->regs.eip = (u32)code;
  gl_current_task->regs.eflags = 0x200;
  gl_current_task->esp0 = KESP;
  gl_current_task->ss0 = 0x10;
  /* Some basic pointers - code addr, data addr, state */
  gl_current_task->p_code = code;
  gl_current_task->p_code_size = file->inode->size;
  gl_current_task->p_data = (void *)((u32)gl_current_task->p_code + file->inode->size);
  gl_current_task->brk = gl_current_task->p_data;
  gl_current_task->state = RUNNING;
  return (1);
}
