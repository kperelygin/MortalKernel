/*
** free_list.c for mk in /home/duc_l/duc_l_mk/Kernel/src/lib
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Mon Jun 29 14:00:27 2009 Duc Lionel
** Last update Mon Jun 29 14:00:46 2009 Duc Lionel
*/

#include "libkern.h"
#include "ctypes.h"
#include "malloc.h"

void	free_list(t_list *begin, void (*data_destruct)())
{
  t_list	*n;
  t_list	*k;

  n = begin;
  while (n)
    {
      k = n;
      n = n->next;
      if (k->data)
	data_destruct(k->data);
      kfree(k);
    }
}

void	free_dlist(t_dlist *begin, void (*data_destruct)())
{
  t_dlist	*n;
  t_dlist	*k;

  n = begin;
  while (n)
    {
      k = n;
      n = n->next;
      if (k->data)
	data_destruct(k->data);
      kfree(k);
    }
}
