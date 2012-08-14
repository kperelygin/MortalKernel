/*
** pic.c for mk in /home/mk/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Sat Feb  7 18:07:47 2009 Mortal Kernel
** Last update Thu Mar 12 14:32:35 2009 Duc Lionel
*/

#include "interrupts.h"
#include "io.h"

void	reload_pic()
{
  outbp(0x20, 0x11); //ICW1 du maitre => 00010001
  outbp(0xA0, 0x11); //esclave

  outbp(0x21, 0x20); //les IRQs du maitre (0 - 7) du PIC1 commencent a 0x20 (32)
  outbp(0xA1, 0x40); //8 - 15 (esclave) mappees sur les int 0x70 - 0x78 (valeur par defaut)

  outbp(0x21, 0x04); //00000100 => la broche 2 (3e irq) sert aux 2 PIC pour communiquer
  outbp(0xA1, 0x04);

  outbp(0x21, 0x01); //mode (valeur par defaut)
  outbp(0xA1, 0x01);

  outbp(0x21, 0x00); //aucune int masquee
  outbp(0xA1, 0xFF);
}
