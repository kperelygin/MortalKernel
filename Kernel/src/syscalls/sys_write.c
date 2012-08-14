/*
** sys_write.c for mk in /home/duc_l/duc_l_mk/Kernel/src/syscalls
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Fri Jul  3 14:57:46 2009 Duc Lionel
** Last update Fri Jul 10 04:17:47 2009 Mortal Kernel
*/

#include "libkern.h"
#include "fs.h"
#include "task.h"
#include "screen.h"
#include "syscall.h"

static int	write_term(void *buff, int bufflen)
{
  void		*p;

  for (p = buff; bufflen > 0; bufflen--)
    {
      vga_out_char(*((char*)buff));
      buff++;
    }
  return (buff - p);
}

int		sys_write(const int fd, void *buff, int bufflen)
{
  t_open_file	*f;
  t_task	*p = gl_current_task;
  int		cc;

  if (fd + 1 > p->opened_files)
    return (-1);
  if (fd < 0)
    return (-2);
  if (!p->files[fd]->file)
    return (write_term(buff, bufflen));
  f = p->files[fd];
  if (!(f->flags & O_RDWR))
    return (-3);
  cc = write_file(f->file, f->offset, buff, bufflen);
  return (cc);
}
