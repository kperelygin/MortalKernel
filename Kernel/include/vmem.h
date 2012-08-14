/*
** memory_management.h for  in /home/mk/kernel_svn/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Fri Feb 20 13:37:21 2009 Mortal Kernel
** Last update Fri Jul 10 21:28:29 2009 Duc Lionel
*/

#ifndef __MEM_MANAGE__
# define __MEM_MANAGE__

# include "ctypes.h"

# define PAGE_SIZE		0x1000 /*4096*/
# define PAGES_PER_TABLE	0x400 /*1024*/
# define TABLES_PER_DIR		0x400

# define NO_MEM			0xFFFFFFFF

# define NEXT_PAGE(page)	(((page) + 1) % (PAGE_SIZE))

enum	e_page_flags {
  PTE_PRESENT = 0x1,
  PTE_RW = 0x2,
  PTE_USER = 0x4,
  PTE_WRITETHROUGH = 0x8, /*for cache*/
  PTE_NOT_CACHEABLE = 0x10,
  PTE_ACCESSED = 0x20,
  PTE_UNUSED = 0x40,
  PTE_SIZE = 0x80,
  PTE_CPU_GLOBAL = 0x100,
  PTE_LV4_GLOBAL = 0x200,
  PTE_FRAME = 0xFFFFF000
};

typedef struct	s_page_table_entry
{
  u32		present: 1;
  u32		rw: 1;
  u32		user: 1;
  u32		pwt: 1;
  u32		pcd: 1;
  u32		accessed: 1;
  u32		dirty: 1;
  u32		size: 1;
  u32		global: 1;
  u32		user_bits: 3;
  u32		base: 20;
}		t_pt_entry;

typedef struct	s_page_dir_entry
{
  u32		present: 1;
  u32		rw: 1;
  u32		user: 1;
  u32		pwt: 1;
  u32		pcd: 1;
  u32		accessed: 1;
  u32		dirty: 1;
  u32		size: 1;
  u32		global: 1;
  u32		user_bits: 3;
  u32		base: 20;
}		t_dir_entry;

struct			s_page_table
{
  t_pt_entry		page[PAGES_PER_TABLE];
};

struct			s_page_directory
{
  t_dir_entry		table[TABLES_PER_DIR];
};

typedef struct s_page_directory	t_page_dir;
typedef struct s_page_table	t_page_tab;

extern t_page_dir	*kdir;
extern int		gl_tab_max;
extern u32		initial_ebp;
extern u32		initial_esp;

/* prototypes */
t_page_dir	*init_paging(u32 memsize);
void		*page_alloc(struct s_page_directory *dir,
			    int pnum, int attributes, int is_kernel);
void		page_free(t_pt_entry *entry);
t_pt_entry	*get_page_entry(t_page_dir *dir, void *addr);
void		*get_phys_addr(void *vaddr, t_page_dir *dir);
t_pt_entry	*get_page(void *vaddr, t_page_dir *dir, u32 *page);
t_page_tab	*get_table(void *vaddr, t_page_dir *dir, u32 *tb);
void		copy_frame(void *dst, void *src);

#endif /* !__MEM_MANAGE__ */
