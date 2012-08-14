/*
** sys_open.c for mk in /home/duc_l/duc_l_mk/Kernel
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Mon Jul  6 20:15:27 2009 Duc Lionel
** Last update Sat Jul 11 01:10:58 2009 Duc Lionel
*/

#include "fs.h"
#include "kstdarg.h"
#include "syscall.h"
#include "task.h"
#include "malloc.h"

static int	open_slot(t_task *p)
{
  int		i;
  t_open_file	**newfiles;

  i = 0;
  while (i < p->opened_files)
    {
      if (p->files[i] == NULL)
	return (i);
      i++;
    }
  newfiles = kmalloc(sizeof(*newfiles) * (p->opened_files + 1));
  newfiles[i] = kmalloc(sizeof(*newfiles[i]));
  if (p->opened_files)
    {
      kmemcpy(newfiles, p->files, sizeof(*newfiles) * (p->opened_files));
      kfree(p->files);
    }
  p->files = newfiles;
  p->opened_files++;
  return (i);
}

static int	open_file(t_node *file, int flags)
{
  int		slot;
  t_task	*p;

  p = gl_current_task;
  slot = open_slot(p);
  p->files[slot]->file = file;
  p->files[slot]->offset = (flags & O_APPEND) ? file->inode->size : 0;
  p->files[slot]->flags = flags;
  return (slot);
}

int		sys_open(const char *path, int flags, ...)
{
  va_list	ap;
  int		mode;
  t_node	*file;
  int		fd;
  const char	*realpath;

  if (path[0] != '/')
    realpath = resolve_relative_path(gl_current_task->cwd, (char *)path);
  else
    realpath = path;
  va_start(ap, flags);
  if (flags & O_CREAT)
    mode = va_arg(ap, int);
  va_end(ap);
  file = path_to_node(gl_vfs, (char *)realpath);
  if (!file)
    {
      if (!(flags & O_CREAT))
	return (-1);
      else
	file = create_file((char *)realpath, mode);
      if (!file)
	return (-1);
    }
  fd = open_file(file, flags);
  return (fd);
}
