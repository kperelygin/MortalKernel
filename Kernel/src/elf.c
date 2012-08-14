/*
** elf.c for mk in /home/mk/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Thu Jul  9 23:49:32 2009 Mortal Kernel
** Last update Fri Jul 10 13:59:43 2009 Duc Lionel
*/

#include "vmem.h"
#include "phy_mem.h"
#include "fs.h"
#include "elf.h"
#include "malloc.h"
#include "task.h"

static int	is_valid_elf(char *buff)
{
  Elf32_Ehdr	*hdr;

  hdr = (Elf32_Ehdr *)buff;
  if (hdr->e_ident[0] == 0x7f &&
      hdr->e_ident[1] == 'E' &&
      hdr->e_ident[2] == 'L' &&
      hdr->e_ident[3] == 'F')
    return (1);
  return (0);
}

static void	cp_headers(Elf32_Ehdr *ehdr, t_node *file)
{
  char		*p;
  Elf32_Phdr	*phdr;
  void		*phdr_buff;
  void		*buff;
  u32		i;
  u32		v_begin;
  u32		v_end;
  u32		v_addr;
  t_pt_entry	*pt;

  i = 0;
  phdr_buff = kmalloc(sizeof(*phdr) * ehdr->e_phnum);
  read_file(file, ehdr->e_phoff, phdr_buff, ehdr->e_phnum * sizeof(*phdr));
  phdr = (Elf32_Phdr *)(phdr_buff);
  while (i < ehdr->e_phnum)
    {
      if (phdr->p_type == PT_LOAD)
	{
	  v_begin = phdr->p_vaddr;
	  v_end = phdr->p_vaddr + phdr->p_memsz;
	  v_addr = v_begin;
	  while (v_addr < v_end)
	    {
	      pt = get_page((void *)v_addr, gl_current_task->page_dir, NULL);
	      pt->present = 1;
	      pt->rw = 1;
	      pt->user = 1;
	      pt->base = (pmem_alloc(0) / PAGE_SIZE);
	      v_addr += PAGE_SIZE;
	    }
	  buff = kmalloc(phdr->p_filesz);
	  kmemset(buff, 0, phdr->p_filesz);
	  read_file(file, phdr->p_offset, buff, phdr->p_filesz);
	  kmemcpy((char *)v_begin, (char *)buff, phdr->p_filesz);
	  if (phdr->p_memsz > phdr->p_filesz)
	    for (i = phdr->p_filesz, p = (char *)phdr->p_vaddr; i < phdr->p_memsz; i++)
	      p[i] = 0;
	}
      phdr++;
      i++;
    }
  kfree(phdr_buff);
}

void		*load_elf(t_node *file)
{
  Elf32_Ehdr	*ehdr;
  void		*ehdr_buff;
  void		*eip;

  ehdr_buff = kmalloc(sizeof(*ehdr));
  read_file(file, 0, ehdr_buff, sizeof(*ehdr));
  ehdr = (Elf32_Ehdr *)ehdr_buff;;
  if (!is_valid_elf(ehdr_buff))
    {
      kfree(ehdr_buff);
      return (NULL);
    }
  cp_headers(ehdr, file);
  eip = (void *)ehdr->e_entry;
  kfree(ehdr_buff);
  return (eip);
}
