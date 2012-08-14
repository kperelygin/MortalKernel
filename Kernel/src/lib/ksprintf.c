/*
** my_printf.c for my_printf in /u/epitech_2012/duc_l/cu/rendu/lib/my2
** 
** Made by lionel duc
** Login   <duc_l@epitech.net>
** 
** Started on  Sat Jan 19 01:46:05 2008 lionel duc
** Last update Mon Jun 29 14:13:15 2009 Duc Lionel
*/

#include "kstdarg.h"
#include "libkern.h"

char	*revstr(char *str)
{
  int	i;
  int	n;
  int	mid;
  char	swap;

  i = 0;
  n = 0;
  while (str[i] != '\0')
    i++;
  mid = i / 2;
  i--;
  while (n < mid)
    {
      swap = str[n];
      str[n] = str[i];
      str[i] = swap;
      n++;
      i--;
    }
  return (str);
}

int	sputnbr(char * __restrict str, int n)
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
    revstr(buff + 1);
  else
    revstr(buff);
  kmemcpy(str, buff, kstrlen(buff) + 1);
  return (i);
}

int	sputstr(char * __restrict dst, const char *str)
{
  int	a;

  a = 0;
  while ((*dst++ = *str++) != 0)
    a++;
  return (a);
}

int	sputnbr_base(char * __restrict str, int n, char *base)
{
  char	buff[65];
  int	i;
  int	b;

  b = kstrlen(base);
  i = 0;
  do
    {
      buff[i] = base[n % b];
      n = n / b;
      i++;
    }
  while (n != 0);
  buff[i] = 0;
  revstr(buff);
  kmemcpy(str, buff, kstrlen(buff) + 1);
  return (i);
}

int		ksprintf(char * __restrict str, char *fmt, ...)
{
  va_list	ap;
  int		a;
  char		c;
  int		t;

  a = 0;
  va_start(ap, fmt);
  while (*fmt != '\0')
    {
      if (*fmt == '%')
	{
	  fmt++;
	  if (*fmt == 'd' || *fmt == 'i')
	    {
	      t = sputnbr(str, va_arg(ap, int));
	      a += t;
	      str += t;
	    }
	  else if (*fmt == 's')
	    {
	      t = sputstr(str, va_arg(ap, char *));
	      a += t;
	      str += t;
	    }
	  else if (*fmt == 'c')
	    {
	      c = va_arg(ap, int);
	      *str++ = (char)c;
	      a++;
	    }
	  else if (*fmt == 'x')
	    {
	      t = sputnbr_base(str, va_arg(ap, int), _HEXA);
	      a += t;
	      str += t;
	    }
	}
      else
	{
	  *str++ = *fmt;
	  a++;
	}
      fmt++;
    }
  *str = 0;
  return (a);
}
