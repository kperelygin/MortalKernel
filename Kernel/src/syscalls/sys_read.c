/*
** sys_read.c for mk in /home/duc_l/duc_l_mk/Kernel/src/syscalls
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Fri Jul  3 15:37:48 2009 Duc Lionel
** Last update Sat Jul 11 01:43:09 2009 Duc Lionel
*/

#include "libkern.h"
#include "fs.h"
#include "task.h"
#include "screen.h"

int	gl_newcode = 0;

int	read_term(u8 *buff, int bufflen)
{
  int	i;
  int	cont = 1;

  i = 0;
  while (cont)
    {
      while (!gl_newcode)
	keyboard_isr(0);
      if (i < bufflen)
	{
	  vga_out_char(gl_newcode);
	  if (gl_newcode == 8)
	    i--;
	  else
	    buff[i++] = gl_newcode;
	}
      if (gl_newcode == 10)
	break;
      gl_newcode = 0;
    }
  while (keyboard_isr(0));
  return (i);
}

int	sys_read(const int fd, void *buff, int bufflen)
{
  t_task	*p = gl_current_task;
  int		cc;

  if (fd + 1 > p->opened_files)
    return (-1); //return error code instead
  if (fd < 0)
    return (-2);
  if (!p->files[fd]->file)
    return (read_term(buff, bufflen));
  cc = read_file(p->files[fd]->file, p->files[fd]->offset, buff, bufflen);
  if (cc == -1)
    return (-3);
  p->files[fd]->offset += cc;
  return (cc);
}
