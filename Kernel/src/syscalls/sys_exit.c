/*
** sys_exit.c for mk in /home/duc_l/duc_l_mk
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Wed Jul  8 22:50:02 2009 Duc Lionel
** Last update Fri Jul 10 22:11:18 2009 Duc Lionel
*/

#include "task.h"

int	sys_exit(int val)
{
  gl_current_task->exit_status = val;
  gl_current_task->state = DELETE;
 change_to_next_task:
  if (gl_current_task)
    gl_current_task = gl_current_task->next;
  else
    gl_current_task = gl_tasklist;

  if (gl_current_task->state != RUNNING)
    {
      if (gl_current_task->state == DELETE)
	kill(gl_current_task);
      goto change_to_next_task;
    }
  switch_to_task(USERMODE);
  return (1);
}
