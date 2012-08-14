/*
** kprintf.c for mk in /home/mk/duc_l_mk/Kernel/src/lib
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Wed Feb  4 23:43:50 2009 Mortal Kernel
** Last update Tue Mar  3 11:44:07 2009 Mortal Kernel
*/

#include "kstdarg.h"
#include "libkern.h"

void		kprintf(char *fmt, ...)
{
  va_list	ap;
  char		c;

  va_start(ap, fmt);
  while (*fmt)
    {
      if (*fmt == '%')
	{
	  fmt++;
	  if (*fmt == 'd' || *fmt == 'i')
	    kputnbr(va_arg(ap, int));
	  else if (*fmt == 's')
	    kputstr(va_arg(ap, char *));
	  else if (*fmt == 'c')
	    {
	      c = va_arg(ap, int);
	      kputchar(c);
	    }
	  else if (*fmt == 'x')
	    kputnbr_base(va_arg(ap, unsigned int), _HEXA);
	}
      else
	kputchar(*fmt);
      fmt++;
    }
  va_end(ap);
}
