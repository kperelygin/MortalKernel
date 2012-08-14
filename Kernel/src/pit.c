/*
** pit.c for mk in /home/mk/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Fri Feb 13 09:10:49 2009 Mortal Kernel
** Last update Fri Feb 13 14:13:51 2009 Duc Lionel
*/

#include "io.h"
#include "timer.h"

#define PIT_FREQUENCY	11931380

void	init_pit(int frequency)
{
  u16	div;

  /*Calculer diviseur*/
  div = PIT_FREQUENCY / frequency;
  outb(0x43, 0x36);
  outb(0x40, div & 0xFF);
  outb(0x40, div >> 8);
  _timet = 0;
}
