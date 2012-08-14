/*
** sys_lseek.c for  in /home/mk/duc_l_mk/Kernel/src/syscalls
** 
** Made by Charlie Root
** Login   <mk@epitech.net>
** 
** Started on  Tue Jul  7 14:47:11 2009 Charlie Root
** Last update Wed Jul  8 14:12:05 2009 Duc Lionel
*/

#include "libkern.h"
#include "fs.h"
#include "task.h"
#include "malloc.h"

int		sys_close(int fd)
{
  t_task	*p;

  p = gl_current_task;
  if (fd < 0 || fd >= p->opened_files)
    return (-1);
  if (p->files[fd] == NULL)
    return (-2);
  kfree(p->files[fd]);
  p->files[fd] = NULL;
  return (0);
}
