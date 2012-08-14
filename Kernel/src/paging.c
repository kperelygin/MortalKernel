/*
** paging.c for  in /home/mk/kernel_svn/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Fri Feb 20 13:36:37 2009 Mortal Kernel
** Last update Wed Jul  1 13:51:37 2009 Mortal Kernel
*/

#include "ctypes.h"
#include "vmem.h"
#include "phy_mem.h"
#include "io.h"
#include "libkern.h"


/*
** 1 table manages 4 MB (1024 * 4096 = 0x400 * 0x1000 = 0x400000)
** 1 directory can manage 4 GB (4MB * 1024 = 4MB * 0x400 = 4GB)
*/

int		gl_tab_max = 0;

t_page_dir	*init_paging(u32 memsize)
{
  t_page_dir	*dir;
  t_page_tab	*tab;
  int		i;
  int		j;
  int		total_page;
  u32		table_addr;
  u32		phys_addr;

  gl_tab_max = memsize / 0x400000;
  dir = (t_page_dir *)pmem_alloc(1);
  i = 0;
  while (i < gl_tab_max)
    {
      table_addr = pmem_alloc(1);
      dir->table[i].base = (u32)(table_addr / PAGE_SIZE);
      dir->table[i].present = 1;
      dir->table[i].rw = 1;
      dir->table[i].user = 0;
      dir->table[i].size = 0;
      i++;
    }
  while (i < TABLES_PER_DIR)
    dir->table[i++].present = 0;
  i = 0;
  phys_addr = 0;
  total_page = 0;
  while (i < gl_tab_max)
    {
      tab = (t_page_tab *)(dir->table[i].base * PAGE_SIZE);
      j = 0;
      while (j < PAGES_PER_TABLE)
	{
	  tab->page[j].base = phys_addr / PAGE_SIZE;
	  if (total_page < PMEM_RESTRICTED_FRAMES + (gl_tab_max + 1))
	    {
	      tab->page[j].present = 1;
	      tab->page[j].rw = 1;
	      tab->page[j].user = 0;
	    }
	  phys_addr += PAGE_SIZE;
	  j++;
	  total_page++;
	}
      i++;
    }
  CLI();
  asm("		mov %0, %%eax    \n \
                mov %%eax, %%cr3 \n \
                mov %%cr0, %%eax \n \
                or %1, %%eax     \n \
                mov %%eax, %%cr0" :: "r"(dir), "i"(0x80000000));
  STI();
  return (dir);
}
