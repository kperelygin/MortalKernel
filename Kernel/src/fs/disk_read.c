/*
** disk_read.c for mk in /home/duc_l/duc_l_mk/Kernel/src
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Thu Mar 12 10:37:15 2009 Duc Lionel
** Last update Tue Jun 30 12:14:50 2009 Duc Lionel
*/

#include "fs.h"

int	disk_read(int start, void *buff, u32 len)
{
  int	count;
  int	a;

  count = len / BYTES_PER_SECTOR;
  if (len % BYTES_PER_SECTOR > 0)
    count++;
  a = ata_read(gl_sel_port, 0, start, count, buff, len);
  return (a);
}
