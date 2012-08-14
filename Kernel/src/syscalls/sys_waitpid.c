/*
** sys_waitpid.c for m in /home/duc_l/duc_l_mk/Kernel/src
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Thu Jul  9 00:43:23 2009 Duc Lionel
** Last update Sat Jul 11 00:08:10 2009 Duc Lionel
*/

#include "task.h"
#include "syscall.h"

static t_task	*find_child(t_task *p, int pid)
{
  t_task	*n;

  n = p;
  while (n)
    {
      if (n->pid == pid)
	{
	  if (n->parent && n->parent->pid == p->pid)
	    return (n);
	  else
	    return (NULL);
	}
      n = n->next;
      if (n == p)
	break;
    }
  return (NULL);
}

int		sys_waitpid(int pid, int *status, int options)
{
  t_task	*p;
  t_task	*son;
  int		child_pid;

  p = gl_current_task;
  son = find_child(p, pid);
  if (!son)
    return (-1);
  child_pid = son->pid;
  if (son->state == DELETE)
    {
      *status = son->exit_status;
      if (!(options & WNOWAIT))
	rm_from_clist(son);
      return (child_pid);
    }
  return (0);
}
