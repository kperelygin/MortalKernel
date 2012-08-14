/*
** sys_dbgprocs.c for mk in /home/duc_l/duc_l_mk
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Sat Jul 11 03:14:40 2009 Duc Lionel
** Last update Sat Jul 11 03:24:19 2009 Duc Lionel
*/

#include "syscall.h"
#include "task.h"

static char	*gl_states[] =
  {
    "sleep", /*Never go here*/
    "run",
    "daemon",
    "sleep",
    "exit",
    "exit"
  };

int		sys_dbgprocs()
{
  t_task	*p = gl_current_task;

  kprintf(" PID   STAT   COMMAND\n");
  while (p)
    {
      kprintf(" %d     %s    %s\n", p->pid, gl_states[p->state], p->name);
      p = p->next;
      if (p == gl_current_task)
	break;
    }
  return (0);
}
