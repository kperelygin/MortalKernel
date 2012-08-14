/*
** ktask.c for mortal kernel in /home/mk/duc_l_mk
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Tue Jun 30 06:23:03 2009 Mortal Kernel
** Last update Sat Jul 11 00:06:58 2009 Duc Lionel
*/

#include "interrupts.h"
#include "vmem.h"
#include "libkern.h"
#include "task.h"
#include "malloc.h"

void		switch_to_task(u32 mode)
{
  u32		kesp;
  u16		kss;

  ktss.ss0 = gl_current_task->ss0;
  ktss.esp0 = gl_current_task->esp0;

  kss = (mode == USERMODE) ? gl_current_task->ss0 : gl_current_task->regs.ss;
  kesp = (mode == USERMODE) ? gl_current_task->esp0 : gl_current_task->regs.esp;

  gl_current_task->regs.eflags = ((gl_current_task->regs.eflags | 0x200) & 0xFFFFBFFF);

  asm volatile("mov %0, %%ss" :: "m"(kss));
  asm volatile("mov %0, %%esp" :: "m"(kesp));
  asm volatile("mov %0, %%eax" :: "m"(gl_current_task->page_dir));
  asm volatile("mov %eax, %cr3");

  /* For IRET */
  if (gl_current_task->regs.cs != 0x08)
    {
      asm volatile("push %0" :: "m"(gl_current_task->regs.ss));
      asm volatile("push %0" :: "m"(gl_current_task->regs.esp));
    }
  asm volatile("push %0" :: "m"(gl_current_task->regs.eflags));
  asm volatile("push %0" :: "m"(gl_current_task->regs.cs));
  asm volatile("push %0" :: "m"(gl_current_task->regs.eip));

  /* Saved Registers */
  asm volatile("push %0" :: "m"(gl_current_task->regs.eax));
  asm volatile("push %0" :: "m"(gl_current_task->regs.ecx));
  asm volatile("push %0" :: "m"(gl_current_task->regs.edx));
  asm volatile("push %0" :: "m"(gl_current_task->regs.ebx));
  asm volatile("push %0" :: "m"(gl_current_task->regs.ebp));
  asm volatile("push %0" :: "m"(gl_current_task->regs.esi));
  asm volatile("push %0" :: "m"(gl_current_task->regs.edi));
  asm volatile("push %0" :: "m"(gl_current_task->regs.ds));
  asm volatile("push %0" :: "m"(gl_current_task->regs.es));
  asm volatile("push %0" :: "m"(gl_current_task->regs.fs));
  asm volatile("push %0" :: "m"(gl_current_task->regs.gs));
  asm volatile("ljmp $0x08, $do_switch");
}

/* Function that is called at each timer interrupt. It switches between tasks. */
void		switch_task(t_int_frame *frame)
{
  t_regs	*regs;

  if (!gl_tasklist)
    return;
  if (gl_current_task && gl_current_task == gl_current_task->next)
    return;

  regs = &gl_current_task->regs;
  regs->eflags = frame->eflags;
  regs->cs = frame->cs;
  regs->eip = frame->eip;
  regs->eax = frame->eax;
  regs->ecx = frame->ecx;
  regs->edx = frame->edx;
  regs->ebx = frame->ebx;
  regs->ebp = frame->ebp;
  regs->esi = frame->esi;
  regs->edi = frame->edi;
  regs->ds = frame->ds;
  regs->es = frame->es;
  regs->fs = frame->fs;
  regs->gs = frame->gs;

  regs->esp = (regs->cs != 0x08) ? (frame->useresp) : (frame->esp + 20);
  regs->ss = (regs->cs != 0x08) ? (frame->ss) : (ktss.ss0);

  gl_current_task->ss0 = ktss.ss0;
  gl_current_task->esp0 = ktss.esp0;

 change_to_next_task:
  if (gl_current_task)
    gl_current_task = gl_current_task->next;
  else
    gl_current_task = gl_tasklist;

  if (gl_current_task->state != RUNNING)
    {
      if (gl_current_task->state == DELETE)
	kill(gl_current_task);
      goto change_to_next_task;
    }
  if (gl_current_task->regs.cs != 0x08)
    switch_to_task(USERMODE);
  else
    switch_to_task(KERNELMODE);
}

/* Function to relocate the stack to userspace, or to be precise 0x400000 -> 0x450000 */
static void	move_stack_to_userspace(u32 size)
{
  void		*new_space;
  u32		current_esp;
  u32		current_ebp;
  u32		stack_size;
  u32		pnum;
  u32		*tmp;
  u32		offset;
  u32		i;

  pnum = (size / PAGE_SIZE);
  if ((size % PAGE_SIZE) != 0)
    pnum += 1;
  new_space = page_alloc(kdir, pnum, PTE_RW | PTE_USER, 0);
  kmemset(new_space, 0, pnum * PAGE_SIZE);

  asm volatile("mov %%esp, %0" : "=r" (current_esp));
  asm volatile("mov %%ebp, %0" : "=r" (current_ebp));
  stack_size = initial_ebp - current_esp;
  kmemcpy((u32 *)(((u32)new_space + size) - stack_size), (u32 *)current_esp, stack_size);
  offset = ((u32)(new_space) + size) - initial_ebp;
  i = 0;
  while (i < size)
    {
      tmp = (u32 *)((u32)(new_space) + i);
      if (*tmp >= current_esp && *tmp <= initial_ebp)
	(*tmp) = (*tmp) + offset;
      i += 4;
    }
  initial_ebp += offset;
  initial_esp += offset;
  asm volatile("mov %%esp, %0" : "=r" (current_esp));
  asm volatile("mov %%ebp, %0" : "=r" (current_ebp));
  asm volatile("mov %0, %%esp" : : "r" (current_esp + offset));
  asm volatile("mov %0, %%ebp" : : "r" (current_ebp + offset));
}

/* Initialisation of the first task; the kernel! */
void		init_kernel_task(void)
{
  t_task	*ktask;

  asm volatile("cli");
  move_stack_to_userspace(KSTACK_SIZE);
  ktask = kmalloc(sizeof(*ktask));
  kmemcpy(ktask->name, "kernel_idle", 11);
  ktask->pid = 1;
  ktask->page_dir = kdir;
  ktask->state = RUNNING;
  ktask->brk = ktask->p_code = ktask->p_data = NULL;
  ktask->p_code_size = 0;
  ktask->cwd = path_to_node(gl_vfs, "/");
  ktask->opened_files = 3;
  ktask->files = kmalloc(sizeof(*ktask->files));
  ktask->files[0] = kmalloc(sizeof(*ktask->files[0]));
  ktask->files[0]->file = NULL;
  ktask->files[1] = kmalloc(sizeof(*ktask->files[1]));
  ktask->files[1]->file = NULL;
  ktask->files[2] = kmalloc(sizeof(*ktask->files[2]));
  ktask->files[2]->file = NULL;
  ktask->parent = NULL;
  cat_to_clist(&gl_tasklist, ktask);
  gl_current_task = gl_tasklist;
  asm volatile("mov %%esp, %0" : "=r"(ktask->regs.esp));
  asm volatile("mov %%ebp, %0" : "=r"(ktask->regs.ebp));
  ktask->regs.cs = 0x08;
  ktask->regs.ds = 0x10;
  ktask->regs.ss = 0x10;
  ktask->regs.eip = read_eip();
  if (ktask->regs.eip == 0x12345)
    return;
  /* Just to ensure that everything works we re-jump to the current instruction*/
  switch_registers(ktask->regs.eip, ktask->regs.ebp, ktask->page_dir, ktask->regs.esp);
}
