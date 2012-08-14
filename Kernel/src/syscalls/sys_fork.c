/*
** sys_fork.c for mk in /home/duc_l/duc_l_mk/Kernel
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Wed Jul  8 22:43:31 2009 Duc Lionel
** Last update Sat Jul 11 00:00:04 2009 Duc Lionel
*/

#include "fs.h"
#include "task.h"

int	sys_fork(void)
{
  return (kfork());
}
