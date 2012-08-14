/*
** kputnbr_base.c for mk in /home/mk/duc_l_mk/Kernel/src/lib
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Wed Feb  4 23:29:17 2009 Mortal Kernel
** Last update Wed Feb  4 23:59:52 2009 Mortal Kernel
*/

#include "libkern.h"

void	kputnbr_base(unsigned int n, char *base)
{
  char	buff[65];
  int	i;
  int	lb;

  kmemset(buff, 0, 65);
  lb = kstrlen(base);
  i = 0;
  do
    {
      buff[i] = base[n % lb];
      n = n / lb;
      i++;
    }
  while (n != 0);
  buff[i] = 0;
  krevstr(buff);
  kputstr(buff);
}
