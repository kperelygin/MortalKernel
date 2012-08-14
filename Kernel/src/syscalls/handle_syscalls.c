/*
** handle_syscalls.c for mk in /home/duc_l/duc_l_mk/Kernel/src
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Wed Jul  8 20:21:55 2009 Duc Lionel
** Last update Sat Jul 11 03:16:02 2009 Duc Lionel
*/

#include "syscall.h"
#include "libkern.h"
#include "task.h"


/*
  -- stack user when interrupt occured --

  ------------------EBP------------------
  local variable a
  local variable b
  ...
  push  param1
  push  param2
  mov	eax, syscallnum
  push  eip (<- the regular push before doing syscalls)
  ------------------ESP------------------
*/

void	handle_syscalls(t_int_frame *regs)
{
  int	*uparams;
  int	ret;

  if (regs->cs != 0x08)
    uparams = (int *)regs->useresp;
  else
    uparams = (int *)(regs->esp + 20);
  if (regs->eax == SYS_exit)
    ret = sys_exit(uparams[1]);
  else if (regs->eax == SYS_fork)
    ret = sys_fork();
  else if (regs->eax == SYS_read)
    ret = sys_read(uparams[1], (void *)uparams[2], uparams[3]);
  else if (regs->eax == SYS_write)
    ret = sys_write(uparams[1], (void *)uparams[2], uparams[3]);
  else if (regs->eax == SYS_open)
    ret = sys_open((char *)uparams[1], uparams[2], uparams[3]);
  else if (regs->eax == SYS_close)
    sys_close(uparams[1]);
  else if (regs->eax == SYS_waitpid)
    ret = sys_waitpid(uparams[1], (int *)uparams[2], uparams[3]);
  else if (regs->eax == SYS_chdir)
    ret = sys_chdir((char *)uparams[1]);
  else if (regs->eax == SYS_lseek)
    ret = sys_lseek(uparams[1], uparams[2], uparams[3]);
  else if (regs->eax == SYS_execve)
    ret = sys_execve((char *)uparams[1], (char **)uparams[2], (char **)uparams[3]);
  else if (regs->eax == SYS_getpid)
    ret = sys_getpid();
  else if (regs->eax == SYS_sbrk)
    ret = (int)sys_sbrk(uparams[1]);
  else if (regs->eax == SYS_cwd)
    ret = (int)sys_cwd((char *)uparams[1]);
  else if (regs->eax == SYS_stat)
    ret = sys_stat((char *)uparams[1], (struct stat *)uparams[2]);
  else if (regs->eax == SYS_dbgprocs)
    ret = sys_dbgprocs();
  else
    ret = -1;
  regs->eax = ret;
}
