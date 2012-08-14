/*
** kmalloc.c for mk in /home/duc_l/duc_l_mk/Kernel
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Sun Mar 15 11:59:49 2009 Duc Lionel
** Last update Wed Jul  1 13:53:21 2009 Mortal Kernel
*/

#include "libkern.h"
#include "vmem.h"
#include "malloc.h"

t_kchunk	*gl_freelist = NULL;
t_kchunk	*gl_kfreelist = NULL;

/*
** kmalloc_p fills the pointer with the physical address associated
** with the virtual one.
*/

void		*umalloc_p(u32 size, u32 *phys)
{
  return (kernel_malloc(size, phys, 0));
}

void		*kmalloc_p(u32 size, u32 *phys)
{
  return (kernel_malloc(size, phys, 1));
}

void		*umalloc(u32 size)
{
  return (kernel_malloc(size, NULL, 0));
}

void		*kmalloc(u32 size)
{
  return (kernel_malloc(size, NULL, 1));
}

void		*umalloc_ap(u32 size, u32 *phys)
{
  return (aligned_malloc(size, phys, 0));
}

void		*kmalloc_ap(u32 size, u32 *phys)
{
  return (aligned_malloc(size, phys, 1));
}

static t_kchunk	*search_in_free_blocks(u32 size, int is_kernel)
{
  t_kchunk	*n;
  t_kchunk	*tmp;
  u32		min_size;

  tmp = NULL;
  min_size = 999999;
  n = (is_kernel == 0) ? gl_freelist : gl_kfreelist;
  if (n && n->size >= size)
    {
      min_size = n->size;
      tmp = n;
    }
  while (n)
    {
      if (n->size < min_size && n->size >= size)
	{
	  min_size = n->size;
	  tmp = n;
	}
      n = n->next;
    }
  return (tmp);
}

static void	split_block_end(void *addr, u32 offset, u32 total_size, int is_kernel)
{
  t_kchunk	*split;

  split = addr + offset;
  split->size = total_size - offset - sizeof(*split);
  split->next = NULL;
  split->magic = KFREE_MAGIC;
  add_to_free_list(split, is_kernel);
}

void		*aligned_malloc(u32 size, u32 *phys, int is_kernel)
{
  void		*p;
  u32		new_pages;

  new_pages = (size / PAGE_SIZE);
  if (size != PAGE_SIZE)
    new_pages += 1;
  p = page_alloc(kdir, new_pages, PTE_RW, is_kernel);
  *phys = (u32)get_phys_addr(p, kdir);
  return (p);
}

void		*kernel_malloc(u32 size, u32 *phys, int is_kernel)
{
  t_kchunk	*c;
  void		*p;
  u32		new_pages;

  size += sizeof(*c);
  size = round_pow2(size);
  if (!size)
    return (NULL);
  if ((c = search_in_free_blocks(size - sizeof(*c), is_kernel)) == NULL)
    {
      new_pages = (size / PAGE_SIZE);
      if (size != PAGE_SIZE)
	new_pages += 1;
      p = page_alloc(kdir, new_pages, PTE_RW, is_kernel);
      c = p;
      c->magic = KMALLOC_MAGIC;
      c->size = size - sizeof(*c);
      if (size < new_pages * PAGE_SIZE)
	split_block_end(p, size, (new_pages * PAGE_SIZE), is_kernel);
    }
  else
    {
      c->magic = KMALLOC_MAGIC;
      delete_from_free_list(c, is_kernel);
    }
  if (phys)
    *phys = (u32)get_phys_addr((void *)(c + sizeof(*c)), kdir);
  return ((void *)c + sizeof(*c));
}
