/*
** task.h for mk in /home/duc_l/duc_l_mk/Kernel/src
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Wed Jun 24 19:28:04 2009 Duc Lionel
** Last update Fri Jul 10 04:02:24 2009 Mortal Kernel
*/

#ifndef __TASK_H__
# define __TASK_H__

# include "interrupts.h"
# include "libkern.h"
# include "ctypes.h"
# include "vmem.h"
# include "gdt.h"
# include "fs.h"

# define RUNNING	1
# define ZOMBIE		2
# define SLEEPING	3
# define EXIT		4
# define DELETE		5

# define KSTACK_START	0x400000
# define KSTACK_SIZE	0x50000
# define KESP		(((KSTACK_START) + (KSTACK_SIZE)) - 16)
# define USTACK_START	0x450000
# define USTACK_SIZE	0x50000
# define UESP		(((USTACK_START) + (USTACK_SIZE)) - 16)

# define CODE_START	0x4A0000

# define KERNELMODE	0
# define USERMODE	1

typedef struct	s_regs
{
  u32		eax;
  u32		ecx;
  u32		ebx;
  u32		edx;
  u32		esp;
  u32		ebp;
  u32		esi;
  u32		edi;
  u32		eip;
  u32		eflags;
  u32		cs;
  u32		ss;
  u32		ds;
  u32		es;
  u32		fs;
  u32		gs;
}__attribute__((packed))t_regs;

typedef struct	s_task
{
  int		pid;
  char		name[256];
  u32		ss0;
  u32		esp0;
  u32		exit_status;
  u32		state;
  t_regs	regs;
  void		*p_code;
  void		*p_data;
  void		*brk;
  u32		p_code_size;
  int		opened_files;
  t_page_dir	*page_dir;
  t_open_file	**files;
  t_node	*cwd;
  struct s_task	*parent;
  struct s_task	*next;
}__attribute__((packed))t_task;

extern t_task	*gl_tasklist;
extern t_task	*gl_current_task;

void		cat_to_clist(t_task **begin, void *data);
void		rm_from_clist(t_task *to_kill);
int		kfork();
int		kexec(t_node *file);
void		switch_task(t_int_frame *frame);
void		switch_to_task(u32 mode);
void		init_kernel_task(void);
void		dt_directory(void *addr);
void		dt_memory(void *addr, void *end_addr, t_page_dir *dir);
void		kill(t_task *task);
extern void	do_switch();
extern u32	read_eip(void);
extern void	switch_registers(u32, u32, t_page_dir *, u32);
extern void	activate_paging(void);
extern void	deactivate_paging(void);
extern u32	switch_page_directory(u32);

#endif /*!__TASK_H__*/
