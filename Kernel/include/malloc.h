/*
** malloc.h for mk in /home/duc_l/duc_l_mk/Kernel
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Sun Mar 15 12:00:08 2009 Duc Lionel
** Last update Tue Jun 30 00:47:30 2009 Mortal Kernel
*/

#ifndef __MALLOC_H__
# define __MALLOC_H__

# include "ctypes.h"

# define KMALLOC_MAGIC	0xDEADBEEF
# define KFREE_MAGIC	0x42424242
# define THRESHOLD	16

typedef struct		s_kchunk
{
  u32			magic;
  u32			size;
  struct s_kchunk	*next;
}			t_kchunk;

extern t_kchunk		*gl_freelist;
extern t_kchunk		*gl_kfreelist;

u32	round_pow2(u32 a);

void	*kmalloc(u32 size);
void	*umalloc(u32 size);
void	*kmalloc_p(u32 size, u32 *phys);
void	*umalloc_p(u32 size, u32 *phys);
void	*kmalloc_ap(u32 size, u32 *phys);
void	*umalloc_ap(u32 size, u32 *phys);
void	*kernel_malloc(u32 size, u32 *phys, int is_kernel);
void	*aligned_malloc(u32 size, u32 *phys, int is_kernel);
void	kfree(void *ptr);
void	ufree(void *ptr);
void	free(void *ptr, int is_kernel);
void	add_to_free_list(t_kchunk *free, int is_kernel);
void	delete_from_free_list(void *ptr, int is_kernel);

#endif /*!__MALLOC_H__*/
