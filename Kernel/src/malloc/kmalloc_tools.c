/*
** kmalloc_tools.c for mk in /home/duc_l/duc_l_mk/Kernel/src/malloc
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Sun Mar 15 12:31:17 2009 Duc Lionel
** Last update Sun Mar 15 14:25:37 2009 Duc Lionel
*/

#include "malloc.h"

u32	round_pow2(u32 a)
{
  a--;
  a = (a >> 1) | a;
  a = (a >> 2) | a;
  a = (a >> 4) | a;
  a = (a >> 8) | a;
  a = (a >> 16) | a;
  a++;
  return (a);
}
