/*
** virt_mem.c for  in /home/mk/kernel_svn/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Tue Mar 10 15:46:16 2009 Mortal Kernel
** Last update Thu Jul  9 04:51:14 2009 Mortal Kernel
*/

#include "vmem.h"
#include "phy_mem.h"
#include "vmem.h"
#include "libkern.h"
#include "screen.h"

int		get_consecutive_pages_in_table(t_dir_entry *dir_entry,
					       int range)
{
  int		page;
  t_page_tab	*table;
  int		free;
  int		save;

  table = (t_page_tab *)(dir_entry->base * PAGE_SIZE);
  page = 0;
  free = 0;
  save = -1;
  while (page < PAGES_PER_TABLE)
    {
      if (table->page[page].present == 0)
	{
	  if (!free)
	    save = page;
	  free++;
	}
      if (free == range)
	return (save);
      if (table->page[page].present)
	{
	  free = 0;
	  save = -1;
	}
      page++;
    }
  return (-1);
}

static void	cancel_set(t_page_tab *table, int page, int i)
{
  while (i >= 0)
    {
      table->page[page + i].present = 0;
      i--;
    }
}

static void	set_attributes(t_pt_entry *page, int attr)
{
  if (attr & PTE_RW)
    page->rw = 1;
  if (attr & PTE_USER)
    page->user = 1;
  if (attr & PTE_WRITETHROUGH)
    page->pwt = 1;
  if (attr & PTE_NOT_CACHEABLE)
    page->pcd = 1;
  if (attr & PTE_CPU_GLOBAL)
    page->global = 1;
}

static int	set_pages(t_dir_entry *dir_entry, int page,
			  int range, int attr, int is_kernel)
{
  int		i;
  t_page_tab	*table;
  u32		phy_addr;

  table = (t_page_tab *)(dir_entry->base * PAGE_SIZE);
  i = 0;
  dir_entry->size = 0;
  while (i < range)
    {
      kmemset(&(table->page[page + i]), 0, sizeof(table->page[page + i]));
      table->page[page + i].present = 1;
      if ((phy_addr = pmem_alloc(is_kernel)) == NO_MEM)
	{
	  cancel_set(table, page, i);
	  return (-1);
	}
      phy_addr = phy_addr / PAGE_SIZE;
      table->page[page + i].base = phy_addr;
      set_attributes(&(table->page[page + i]), attr);
      i++;
    }
  dir_entry->present = 1;
  return (0);
}

u32	get_free_page_range(t_page_dir *dir, int range, int attr, int is_kernel)
{
  int	table;
  int	page_num;
  u32	vaddr;
  int	last_table;

  table = (is_kernel == 1) ? 0 : 1;
  last_table = (is_kernel == 1) ? 1 : TABLES_PER_DIR;
  //TODO: Change this, so that it works with multiple tables
  while (table < last_table)
    {
      if ((page_num = get_consecutive_pages_in_table(&(dir->table[table]), range)) != -1)
	{
	  if (set_pages(&(dir->table[table]), page_num, range, attr, is_kernel) < 0)
	    return (NO_MEM);
	  vaddr = table * 0x400000 + page_num * 0x1000;
	  return (vaddr);
	}
      table++;
    }
  return (NO_MEM);
}

void	*page_alloc(t_page_dir *dir, int pnum, int attributes, int is_kernel)
{
  u32	vaddr;
  u32	pd_addr;

  vaddr = get_free_page_range(dir, pnum, attributes, is_kernel);
  if (vaddr == NO_MEM)
    return (NULL);
  //flush the TLB
  asm volatile("mov %%cr3, %0" : "=r" (pd_addr));
  asm volatile("mov %0, %%cr3" : : "r" (pd_addr));
  //return the virtual address
  return ((void *)vaddr);
}

void	page_free(t_pt_entry *entry)
{
  entry->present = 0;
  pmem_free((void *)(entry->base * PAGE_SIZE));
}

t_page_tab	*get_table(void *vaddr, t_page_dir *dir, u32 *tb)
{
  t_page_tab	*table;
  int		pnum;
  int		tb_num;

  pnum = (u32)vaddr / PAGE_SIZE;
  tb_num = pnum / PAGES_PER_TABLE;
  pnum = pnum % PAGES_PER_TABLE;
  table = (t_page_tab *)(dir->table[tb_num].base * PAGE_SIZE);
  if (tb)
    *tb = tb_num;
  return (table);
}

t_pt_entry	*get_page(void *vaddr, t_page_dir *dir, u32 *page)
{
  t_page_tab	*table;
  int		pnum;
  int		tb_num;

  pnum = (u32)vaddr / PAGE_SIZE;
  tb_num = pnum / PAGES_PER_TABLE;
  pnum = pnum % PAGES_PER_TABLE;
  table = (t_page_tab *)(dir->table[tb_num].base * PAGE_SIZE);
  if (page)
    *page = pnum;
  return (&table->page[pnum]);
}

void		*get_phys_addr(void *vaddr, t_page_dir *dir)
{
  t_page_tab	*table;
  int		pnum;
  int		tb_num;

  pnum = (u32)vaddr / PAGE_SIZE;
  tb_num = pnum / PAGES_PER_TABLE;
  pnum = pnum % PAGES_PER_TABLE;
  table = (t_page_tab *)(dir->table[tb_num].base * PAGE_SIZE);
  return ((void *)(table->page[pnum].base * PAGE_SIZE));
}
