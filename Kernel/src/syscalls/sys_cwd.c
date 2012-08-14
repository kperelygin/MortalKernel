/*
** sys_chdir.c for  in /home/mk/duc_l_mk/Kernel/src/libumk
** 
** Made by Charlie Root
** Login   <mk@epitech.net>
** 
** Started on  Wed Jul  8 14:51:44 2009 Charlie Root
** Last update Fri Jul 10 23:54:07 2009 Duc Lionel
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

int		sys_cwd(char *path)
{
  char		*realpath;

  realpath = resolve_relative_path(gl_current_task->cwd, ".");
  if (kstrlen(realpath) > 0)
    kmemcpy(path, realpath, kstrlen(realpath) - 1);
  else
    kmemcpy(path, realpath, kstrlen(realpath));
  return (0);
}
