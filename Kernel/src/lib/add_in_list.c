/*
** add_in_list.c for mk in /home/duc_l/duc_l_mk/Kernel/src/lib
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Mon Jun 29 13:58:54 2009 Duc Lionel
** Last update Fri Jul 10 14:54:08 2009 Duc Lionel
*/

#include "malloc.h"
#include "ctypes.h"
#include "libkern.h"

void		add_in_list(t_list **list, void *data)
{
  t_list	*new;

  new = kmalloc(sizeof(*new));
  new->data = data;
  new->next = *list;
  *list = new;
}

void		add_in_dlist(t_dlist **list, void *data)
{
  t_dlist	*new;

  new = kmalloc(sizeof(*new));
  new->data = data;
  new->next = *list;
  new->prev = NULL;
  if (*list)
    (*list)->prev = new;
  *list = new;
}

void		cat_to_list(t_list **begin, void *data)
{
  t_list	*n;
  t_list	*new;

  new = kmalloc(sizeof(*new));
  new->data = data;
  new->next = 0;
  n = *begin;
  if (*begin == NULL)
    {
      *begin = new;
    }
  else
    {
      while (n->next != 0)
	n = n->next;
      n->next = new;
    }
}
