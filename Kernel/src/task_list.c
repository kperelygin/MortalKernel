/*
** task_list.c for mk in /home/mk/duc_l_mk/Kernel
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Thu Jul  9 05:39:24 2009 Mortal Kernel
** Last update Thu Jul  9 06:07:15 2009 Mortal Kernel
*/

#include "libkern.h"
#include "task.h"
#include "malloc.h"


/* Function to add a task to the process list */
void		cat_to_clist(t_task **begin, void *data)
{
  t_task	*new;
  t_task	*tmp;

  new = data;
  if (*begin == NULL)
    {
      new->next = new;
      *begin = new;
    }
  else
    {
      tmp = *begin;
      while (tmp->next != *begin)
	tmp = tmp->next;
      new->next = *begin;
      tmp->next = new;
    }
}

/* Function to remove from process list */
void		rm_from_clist(t_task *to_kill)
{
  t_task        *save;

  if (gl_tasklist->next == gl_tasklist)
    return;
  if (to_kill == gl_tasklist)
    gl_tasklist = gl_tasklist->next;
  else
    {
      save = gl_tasklist;
      while (save && save->next != to_kill)
        save = save->next;
      save->next = to_kill->next;
    }
  kfree(to_kill);
}
