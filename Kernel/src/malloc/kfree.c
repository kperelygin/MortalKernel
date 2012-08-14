/*
** kfree.c for mk in /home/duc_l/duc_l_mk
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Sun Mar 15 14:26:40 2009 Duc Lionel
** Last update Thu Jul  9 03:05:42 2009 Mortal Kernel
*/

#include "libkern.h"
#include "vmem.h"
#include "malloc.h"

void		add_to_free_list(t_kchunk *free, int is_kernel)
{
  t_kchunk      *tmp;

  tmp = ((is_kernel == 0) ? gl_freelist : gl_kfreelist);
  if (tmp == NULL)
    ((is_kernel == 0) ? (gl_freelist = free) : (gl_kfreelist = free));
  else
    {
      while (tmp->next)
        tmp = tmp->next;
      tmp->next = free;
    }
}

void		delete_from_free_list(void *ptr, int is_kernel)
{
  t_kchunk      *tmp;
  t_kchunk      *tmp2;

  tmp = (is_kernel == 0) ? gl_freelist : gl_kfreelist;
  if (tmp == ptr)
    ((is_kernel == 0) ? (gl_freelist = tmp->next) : (gl_kfreelist = tmp->next));
  else if (tmp->next)
    {
      while (tmp->next)
        {
          if (tmp->next == ptr)
            {
              tmp2 = tmp;
              tmp = tmp->next;
              tmp2->next = tmp->next;
              break;
            }
          else
            tmp = tmp->next;
        }
    }
  else
    ((is_kernel == 0) ? (gl_freelist = NULL) : (gl_kfreelist = NULL));
}

void		ufree(void *ptr)
{
  free(ptr, 0);
}

void		kfree(void *ptr)
{
  free(ptr, 1);
}

void		free(void *ptr, int is_kernel)
{
  t_kchunk	*free;

  free = ptr - sizeof(*free);
  if (free->magic == KFREE_MAGIC)
    kprintf("Warning: Pointer (0x%x) is already free.\n", ptr);
  else if (free->magic == KMALLOC_MAGIC)
    {
      free->magic = KFREE_MAGIC;
      free->next = NULL;
      add_to_free_list(free, is_kernel);
    }
  else
    kprintf("Warning: Pointer (0x%x) is not a valid block.\n", ptr);
}
