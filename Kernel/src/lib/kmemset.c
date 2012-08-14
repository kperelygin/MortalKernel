/*
** kmemset.c for mk in /home/duc_l/duc_l_mk/Kernel/src/lib
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Fri Jul  3 20:09:51 2009 Duc Lionel
** Last update Fri Jul  3 20:11:55 2009 Duc Lionel
*/

#include "ctypes.h"

void		*kmemset(void *dst, int c, u32 len)
{
  char		*p;

  p = dst;
  while (len-- != 0)
    *p = c;
  return (dst);
}
