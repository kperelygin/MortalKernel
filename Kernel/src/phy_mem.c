/*
** phy_mem.c for  in /home/mk/kernel_svn/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Tue Mar  3 16:40:13 2009 Mortal Kernel
** Last update Tue Jun 30 17:27:01 2009 Mortal Kernel
*/

#include "phy_mem.h"

u8	pmem_bitmap[PMEM_BITMAP_BYTE];

u32	pmem_alloc(int is_kernel)
{
  u32	i;
  u32	j;
  u32	k;
  u32	l;
  u32	addr;

  if (is_kernel)
    i = 0;
  else
    i = 1024 / 8;
  while (i < PMEM_BITMAP_BYTE && pmem_bitmap[i] == 0xFF)
    i++;
  if (i == PMEM_BITMAP_BYTE)
    return ((u32)-1);
  j = 1;
  k = 0;
  while (j <= 128 && (pmem_bitmap[i] & j))
    {
      j <<= 1;
      k++;
    }
  l = 0;
  addr = 0;
  while (l < (i * 8) + k)
    {
      addr += 4096;
      l++;
    }
  pmem_bitmap[i] |= j;
  return (addr);
}

void	pmem_free(void *p_addr)
{
  u32	mem;
  u32	mid_addr;
  u32	i;
  u32	j;
  u32	mask;
  u32	x;

  mem = (u32)p_addr;
  mid_addr = pmem_get_bitmap_from_addr(p_addr);
  x = mid_addr;
  i = 0;
  while (mid_addr < mem)
    {
      mid_addr += 4096;
      i++;
    }
  mask = 1;
  j = 0;
  while (j < i)
    {
      mask = mask + mask;
      j++;
    }
  pmem_bitmap[x] ^= mask;
}

/*
** init physical memory bitmap : by default the two first 4 Mo are reserved to Kernel
*/

void	pmem_init(void)
{
  u32	i;

  i = 0;
  while (i < PMEM_RESTRICTED_AREA)
    {
      pmem_bitmap[i] |= 0xFF;
      i++;
    }
  while (i < PMEM_BITMAP_BYTE)
    {
      pmem_bitmap[i] = 0x0;
      i++;
    }
}

int	pmem_get_bitmap_from_addr(void *addr)
{
  u32	res;
  u32	mem;
  u32	i;

  mem = (u32)addr;
  i = mem / 4096;
  res = (i + (mem % 4096)) / 8;
  if (res > PMEM_BITMAP_BYTE)
     return (-1);
  return (res);
}
