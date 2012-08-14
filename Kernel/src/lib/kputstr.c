/*
** kputstr.c for mk in /home/mk/duc_l_mk/Kernel/src/lib
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Wed Feb  4 23:25:15 2009 Mortal Kernel
** Last update Wed Feb  4 23:37:31 2009 Mortal Kernel
*/

#include "screen.h"

void	kputstr(char *str)
{
  vga_putstr(str);
}

void	kputchar(char c)
{
  vga_out_char(c);
}
