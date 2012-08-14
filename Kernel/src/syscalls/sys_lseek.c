/*
** sys_lseek.c for  in /home/mk/duc_l_mk/Kernel/src/syscalls
** 
** Made by Charlie Root
** Login   <mk@epitech.net>
** 
** Started on  Tue Jul  7 14:47:11 2009 Charlie Root
** Last update Fri Jul 10 04:17:31 2009 Mortal Kernel
*/

#include "libkern.h"
#include "fs.h"
#include "task.h"
#include "screen.h"
#include "syscall.h"

int		sys_lseek(int fd, int offset, int whence)
{
  t_task	*p;
  t_open_file	*f;
  int		size_file;

  p = gl_current_task;
  if (whence < 0 || whence > 4)
    return (-1);
  if (fd < 0 || fd >= p->opened_files)
    return (-2);
  f = p->files[fd];
  if (!f->file)
    return (-3);
  size_file = f->file->inode->size;
  if (whence == SEEK_SET)
    {
      if (offset < 0)
	f->offset = 0;
      else if (offset > size_file)
	f->offset = size_file;
      else
	f->offset = offset;
    }
  else if (whence == SEEK_CUR)
    {
      if ((f->offset + offset) > size_file)
	f->offset = size_file;
      else
	f->offset = f->offset + offset;
    }
  else if (whence == SEEK_END)
    {
      if (offset > 0)
	f->offset = size_file;
      else if (size_file - offset < 0)
	f->offset = 0;
      else
	f->offset = size_file + offset;
    }
  return (f->offset);
}
