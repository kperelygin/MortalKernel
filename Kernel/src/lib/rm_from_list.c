/*
** rm_from_list.c for mk in /home/duc_l/duc_l_mk/Kernel/src/lib
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Mon Jun 29 14:00:20 2009 Duc Lionel
** Last update Mon Jun 29 14:00:41 2009 Duc Lionel
*/

#include "libkern.h"
#include "ctypes.h"
#include "malloc.h"

void	rm_from_list(t_list **begin, t_list *to_kill,
		     void (*data_destructor)())
{
  t_list	*save;

  if (to_kill == *begin)
    *begin = (*begin)->next;
  else
    {
      save = *begin;
      while (save->next != to_kill)
	save = save->next;
      save->next = to_kill->next;
    }
  if (to_kill->data)
    data_destructor(to_kill->data);
  kfree(to_kill);
}

void	rm_from_dlist(t_dlist **begin, t_dlist *to_kill,
		      void (*data_destructor)())
{
  t_dlist	*save;

  if (to_kill == *begin)
    {
      *begin = (*begin)->next;
      if (*begin)
	(*begin)->prev = 0;
    }
  else
    {
      save = *begin;
      while (save->next != to_kill)
	save = save->next;
      save->next = to_kill->next;
      if (to_kill->next)
	to_kill->next->prev = save;
    }
  if (to_kill->data)
    data_destructor(to_kill->data);
  kfree(to_kill);
}
