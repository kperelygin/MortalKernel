/*
** sys_chdir.c for  in /home/mk/duc_l_mk/Kernel/src/libumk
** 
** Made by Charlie Root
** Login   <mk@epitech.net>
** 
** Started on  Wed Jul  8 14:51:44 2009 Charlie Root
** Last update Fri Jul 10 18:36:19 2009 Duc Lionel
*/

#include "libkern.h"
#include "fs.h"
#include "task.h"
#include "screen.h"
#include "syscall.h"

/* 
convert path to inode and update cwd task 
return 0 on success
return -1 on failure
*/

int		sys_chdir(const char *path)
{
  t_task	*p = gl_current_task;
  t_node	*new_dir;
  const char	*realpath;

  if (path[0] != '/')
    realpath = resolve_relative_path(gl_current_task->cwd, (char *)path);
  else
    realpath = path;
  new_dir = path_to_node(gl_vfs, (char *)realpath);
  if (new_dir == NULL)
    return (-1);
  p->cwd = new_dir;
  return (0);
}
