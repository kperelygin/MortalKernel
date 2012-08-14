/*
** kstrdup.c for mk in /home/duc_l/duc_l_mk/Kernel/src/lib
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Tue Jun 30 05:46:50 2009 Duc Lionel
** Last update Tue Jun 30 05:47:40 2009 Duc Lionel
*/

#include "libkern.h"
#include "malloc.h"

char	*kstrdup(char *s)
{
  char	*p;
  int	len;

  len = kstrlen(s);
  p = kmalloc(sizeof(*p) * (len + 1));
  kmemcpy(p, s, len);
  p[len] = 0;
  return (p);
}
