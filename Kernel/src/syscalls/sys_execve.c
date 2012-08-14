/*
** sys_execve.c for mk in /home/duc_l/duc_l_mk
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Wed Jul  8 22:24:54 2009 Duc Lionel
** Last update Sat Jul 11 01:58:04 2009 Duc Lionel
*/

#include "screen.h"
#include "vmem.h"
#include "syscall.h"
#include "fs.h"
#include "task.h"
#include "malloc.h"
/*
static char	**copy_argv(char **argv)
{
  char		**ptr;
  u32		len;
  u32		i;

  i = 0;
  len = 0;
  while (argv[i])
    i++;
  ptr = kmalloc((sizeof(*argv)) * (i + 1));
  i = 0;
  while (argv[i])
    {
      ptr[i] = kstrdup(argv[i]);
      i++;
    }
  ptr[i] = NULL;
  return (ptr);
}

static void	push_prog_args(t_task *task, char **argv)
{
  int		i;
  int		ac;
  u32		vpushaddr; //virtual address of the next arg to push
  u32		argaddr; //this is virtual &argv[0] that will be pushed for main
  u32		phys; //physical offset of whatever
  u32		data_vplace; //virtual address of the args datas
  u32		remain; //remaining space in the last allocated page in kexec
  u32		needed_space = 0;

  ac = 0;
  for (i = 0; argv[i]; i++)
    {
      needed_space += kstrlen(argv[i]) + 1;
      ac++;
    }
  data_vplace = (u32)task->p_data; //set data_vplace to the beginning of the data section
  remain = PAGE_SIZE - ((u32)task->p_data % PAGE_SIZE); //get the remaining space in the last page
  //if there is not enough, allocate place in users'data for the args (strlen of each)
  while (needed_space > remain)
    {
      page_alloc(task->page_dir, 1, PTE_RW | PTE_USER, 0);
      needed_space -= PAGE_SIZE;
    }
  //now:
  //copy from argv to the physical location of data_vplace
  //task->brk += needed_space;
  vpushaddr = task->regs.esp;
  //push null ptr
  for (i = ac; i > 0; i++)
    {
      //push data_place at vpushaddr
      if (i == 0)
	argaddr = vpushaddr;
      vpushaddr -= 4;
      data_vplace += kstrlen(argv[i]) + 1;
    }
  //push ac
  //now push a fake eip (the one pushed by _start)
  //repush ac
  //push argaddr
}
*/

int		sys_execve(const char *path, __attribute__((unused))char **argv,
			   __attribute__((unused))char **env)
{
  t_node	*file;
  char		**ptr;

  file = path_to_node(gl_vfs, (char *)path);
  if (!file)
    return (-1);
  if (!(file->inode->mode & EXT2_S_IFREG))
    return (-2);
  if (file->inode->size > 0x1000000)
    return (-3);
  ptr = NULL;
  //if (argv)
  //    ptr = copy_argv(argv);
  if (!kexec(file))
    return (-4);
  //push_prog_args(gl_current_task, ptr);
  switch_to_task(USERMODE);
  return (0);
}
