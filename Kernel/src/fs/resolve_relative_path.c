/*
** resolve_relative_path.c for mk in /home/duc_l/duc_l_mk
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Fri Jul 10 14:11:29 2009 Duc Lionel
** Last update Sat Jul 11 01:46:14 2009 Duc Lionel
*/

#include "fs.h"

char	gl_realpath[4096];

static void	revcpy(char *dst, char *src, int len)
{
  while (len > 0)
    {
      dst[len - 1] = src[len - 1];
      len--;
    }
}

char		*resolve_relative_path(t_node *cwd, char *path)
{
  char		tmp[4096];
  int		i;
  int		len;
  t_node	*p;

  kmemset(gl_realpath, 0, 4096);
  tmp[4095] = 0;
  i = 4095;
  len = kstrlen(path);
  i -= len;
  revcpy(tmp + i, path, len);
  p = cwd;
  while (p->parent && i > 0)
    {
      len = kstrlen(p->filename);
      i--;
      revcpy(tmp + i, "/", 1);
      i -= len;
      revcpy(tmp + i, p->filename, len);
      p = p->parent;
    }
  i--;
  revcpy(tmp + i, "/", 1);
  kmemcpy(gl_realpath, tmp + i, 4095 - i);
  gl_realpath[4095 - i] = 0;
  return (gl_realpath);
}
