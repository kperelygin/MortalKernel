/*
** phy_mem.c<2> for  in /home/mk/kernel_svn/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Tue Mar  3 16:40:29 2009 Mortal Kernel
** Last update Tue Jun 30 17:27:06 2009 Mortal Kernel
*/

#ifndef __PHY_MEM__
# define __PHY_MEM__

#include "ctypes.h"

# define PMEM_BITMAP_BYTE	1024 /* manage 32 Mo physical memory (bochs default) */
# define PMEM_RESTRICTED_AREA	32 /*Right after video memory, 0x100k*/
# define PMEM_RESTRICTED_FRAMES 0x100
# define DEFAULT_MEM_SIZE	0x2000000 /*== 32 MB*/

u32	pmem_alloc(int is_kernel);
void	pmem_free(void *p_addr);
void	pmem_init(void);
int	pmem_get_bitmap_from_addr(void *addr);

extern u8 pmem_bitmap[PMEM_BITMAP_BYTE];


#endif /* !__PHY_MEM__ */
