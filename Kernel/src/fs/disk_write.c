/*
** disk_write.c for mk in /home/duc_l/duc_l_mk/Kernel/src/fs
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Tue Jun 30 12:15:02 2009 Duc Lionel
** Last update Tue Jul  7 00:21:09 2009 Duc Lionel
*/

#include "fs.h"
#include "malloc.h"

int	disk_write(int start, void *buff, u32 len)
{
  int	count;
  int	a;

  count = len / BYTES_PER_SECTOR;
  if (len % BYTES_PER_SECTOR > 0)
    count++;
  a = ata_write(gl_sel_port, 0, start, count, buff, len);
  return (a);
}
