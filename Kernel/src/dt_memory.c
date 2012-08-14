/*
** dt_memory.c for mk in /home/mk/duc_l_mk
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Thu Jul  9 05:20:39 2009 Mortal Kernel
** Last update Fri Jul 10 03:23:21 2009 Mortal Kernel
*/

#include "task.h"
#include "vmem.h"
#include "phy_mem.h"

void		dt_directory(void *addr)
{
  t_page_dir	*dir;
  t_pt_entry	*page;
  u32		i;

  i = 0;
  dir = (t_page_dir *)addr;
  while (i < (u32)gl_tab_max)
    {
      addr = (void *)(dir->table[i].base * PAGE_SIZE);
      page = get_page(addr, kdir, NULL);
      page_free(page);
      i++;
    }
  page = get_page(addr, kdir, NULL);
  page_free(page);
}

void		dt_memory(void *addr, void *end_addr, t_page_dir *dir)
{
  u32		i;
  t_pt_entry	*page;

  if ((!addr) || (!end_addr))
    return;
  i = 0;
  while ((addr + i) < end_addr)
    {
      page = get_page((addr + i), dir, NULL);
      if (page->present == 1)
	{
	  page->present = 0;
	  pmem_free((void *)(page->base * PAGE_SIZE));
	}
      i += PAGE_SIZE;
    }
}

void	kill(t_task *task)
{
  if (gl_current_task->brk)
    dt_memory((void *)0x400000, gl_current_task->brk, task->page_dir);
  else
    dt_memory((void *)0x400000, (void *)UESP, task->page_dir);
  dt_directory(task->page_dir);
  task->state = EXIT;
  //TODO
  //Verify that all is freed.
}
