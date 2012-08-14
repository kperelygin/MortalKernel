/*
** kfork.c for Mortal Kernel in /home/mk/duc_l_mk
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Tue Jun 30 00:51:34 2009 Mortal Kernel
** Last update Sat Jul 11 00:07:47 2009 Duc Lionel
*/

#include "vmem.h"
#include "libkern.h"
#include "task.h"
#include "malloc.h"

static t_dir_entry	init_table(t_dir_entry *src)
{
  t_dir_entry		new_entry;
  t_page_tab		*new_page_tab;
  t_page_tab		*src_page_tab;

  src_page_tab = (t_page_tab *)(src->base * PAGE_SIZE);
  new_page_tab = page_alloc(kdir, 1, PTE_RW, 1);
  kmemset(&new_entry, 0, sizeof(new_entry));
  kmemset(new_page_tab, 0, PAGE_SIZE);
  new_entry.base = (u32)new_page_tab / PAGE_SIZE;
  new_entry.present = 1;
  new_entry.rw = 1;
  new_entry.user = 1;
  return (new_entry);
}

static void		clone_table(t_dir_entry *src, t_dir_entry *new, t_page_dir *task_dir)
{
  t_page_tab		*src_page_tab;
  t_page_tab		*new_page_tab;
  u32			*dst_addr;
  u32			*src_addr;
  void			*addr;
  u32			phys;
  int			i;

  src_page_tab = (t_page_tab *)(src->base * PAGE_SIZE);
  new_page_tab = (t_page_tab *)(new->base * PAGE_SIZE);
  i = 0;
  while (i < 1024)
    {
      if (src_page_tab->page[i].present == 1)
	{
	  addr = page_alloc(task_dir, 1, PTE_RW | PTE_USER, 0);
	  phys = (u32)(get_phys_addr(addr, task_dir)) / PAGE_SIZE;
	  new_page_tab->page[i] = src_page_tab->page[i];
	  new_page_tab->page[i].base = phys;
	  dst_addr = (u32 *)(new_page_tab->page[i].base * PAGE_SIZE);
	  src_addr = (u32 *)(src_page_tab->page[i].base * PAGE_SIZE);
	  copy_frame(dst_addr, src_addr);
	}
      i++;
    }
}

t_page_dir		*clone_directory(t_page_dir *src)
{
  t_page_dir		*new;
  int			i;

  new = page_alloc(kdir, 1, PTE_RW, 1);
  kmemset(new, 0, PAGE_SIZE);
  i = 0;
  while (i < 1024)
    {
      if (src->table[i].present == 1)
	{
	  if (i == 0)
	    new->table[i] = src->table[i];
	  else
	    new->table[i] = init_table(&src->table[i]);
	}
      i++;
    }
  i = 0;
  while (i < 1024)
    {
      if (src->table[i].present == 1 && i != 0)
	clone_table(&src->table[i], &new->table[i], new);
      i++;
    }
  return (new);
}

/*
** Kfork will create a new task, which is a replica of the old one.
** It returns the pid of the child to the parent, and 0 to the child.
*/
int		kfork(void)
{
  static u32	pid = 2;
  t_task	*new;
  t_task	*parent_task;
  u32		eip;
  int		i;

  asm volatile("cli");
  parent_task = gl_current_task;
  new = kmalloc(sizeof(*new));
  kmemset(new, 0, sizeof(*new));
  new->pid = pid;
  new->state = RUNNING;
  new->regs.eflags = 0x200;
  new->regs.cs = 0x08;
  new->regs.ds = new->regs.ss = new->regs.es = new->regs.fs = new->regs.gs = 0x10;
  new->parent = gl_current_task;
  new->cwd = parent_task->cwd;
  new->opened_files = parent_task->opened_files;
  new->files = kmalloc(sizeof(*new->files));
  for (i = 0; i < new->opened_files; i++)
    {
      new->files[i] = kmalloc(sizeof(*new->files[i]));
      new->files[i]->file = parent_task->files[i]->file;
      new->files[i]->offset = parent_task->files[i]->offset;
      new->files[i]->flags = parent_task->files[i]->flags;
    }
  pid++;
  cat_to_clist(&gl_tasklist, new);
  eip = read_eip();
  if (gl_current_task == parent_task)
    {
      new->regs.eip = eip;
      new->regs.eax = 0;
      asm volatile("mov %%esp, %0" : "=r"(new->regs.esp));
      asm volatile("mov %%ebp, %0" : "=r"(new->regs.ebp));
      new->page_dir = clone_directory(gl_current_task->page_dir);
      new->ss0 = 0x10;
      new->esp0 = KESP;
      new->brk = NULL;
      asm volatile("sti");
      return (new->pid);
    }
  else
    return (0);
}
