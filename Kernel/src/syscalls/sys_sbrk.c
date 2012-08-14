/*
** sys_sbrk.c for mk in /home/mk/duc_l_mk
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Thu Jul  9 03:59:38 2009 Mortal Kernel
** Last update Thu Jul  9 04:16:45 2009 Mortal Kernel
*/

#include "libkern.h"
#include "vmem.h"
#include "task.h"
#include "malloc.h"

void	*sys_sbrk(u32 incr)
{
  u32	new_pages;
  void	*addr;

  if (incr <= 0)
    return (gl_current_task->brk);
  new_pages = (incr / PAGE_SIZE);
  if (incr != PAGE_SIZE)
    new_pages += 1;
  addr = page_alloc(gl_current_task->page_dir, new_pages, PTE_RW | PTE_USER, 0);
  if (addr == NULL)
    return (NULL);
  gl_current_task->brk = (void *)((u32)gl_current_task->brk + (new_pages * PAGE_SIZE));
  return (addr);
}

