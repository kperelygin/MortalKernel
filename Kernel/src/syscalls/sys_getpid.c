/*
** sys_getpid.c for mk in /home/duc_l/duc_l_mk
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Wed Jul  8 22:52:21 2009 Duc Lionel
** Last update Wed Jul  8 22:52:40 2009 Duc Lionel
*/

#include "task.h"

int	sys_getpid()
{
  return (gl_current_task->pid);
}
