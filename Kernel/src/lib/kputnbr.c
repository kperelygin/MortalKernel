/*
** kputnbr.c for mk in /home/mk/duc_l_mk/Kernel/src/lib
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Wed Feb  4 23:26:35 2009 Mortal Kernel
** Last update Sat Feb  7 22:01:00 2009 Mortal Kernel
*/

#include "libkern.h"

void	kputnbr(int n)
{
  char	buff[21];
  int	i;

  i = 0;
  if (n < 0)
    {
      n = -n;
      buff[i++] = '-';
    }
  do
    {
      buff[i] = n % 10 + '0';
      n = n / 10;
      i++;
    }
  while (n != 0);
  buff[i] = 0;
  if (buff[0] == '-')
    krevstr(buff + 1);
  else
    krevstr(buff);
  kputstr(buff);
}
