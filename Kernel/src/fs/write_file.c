/*
** write_file.c for mk in /home/duc_l/duc_l_mk/Kernel/src
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Fri Jul  3 17:53:42 2009 Duc Lionel
** Last update Sat Jul 11 03:22:28 2009 Duc Lionel
*/

#include "libkern.h"
#include "fs.h"

void	add_indir_block(t_node *file)
{
  int	data[BLOCK_SIZE / 4];
  int	indirblock;
  int	indiridx;

  if (file->inode->blocks == 12)
    file->inode->block[12] = alloc_block(gl_hdd);
  indirblock = file->inode->block[12];
  read_block(indirblock, data);
  indiridx = file->inode->blocks - 12;
  data[indiridx] = alloc_block(gl_hdd);
}

int	add_block_to_file(t_node *file)
{
  int	indir;

  indir = indirect_level(file->inode->blocks);
  if (indir == 0)
    file->inode->block[file->inode->blocks] = alloc_block(gl_hdd);
  else if (indir == 1)
    add_indir_block(file);
  //double indirection
  file->inode->blocks++;
  return (0);
}

void	allocate_needed_blocks(t_node *file, u64 start_off, int buflen)
{
  int	needed;
  int	gap;

  gap = (start_off + buflen) - file->inode->size;
  if (gap <= 0)
    return;
  needed = gap / BLOCK_SIZE;
  if (gap % BLOCK_SIZE)
    needed++;
  while (needed >= 0)
    {
      add_block_to_file(file);
      needed--;
    }
}

int	write_file(t_node *file, u64 start_off, void *buf, int buflen)
{
  char	data[BLOCK_SIZE];
  int	block;
  int	block_off;
  int	save;
  int	copy;
  int	range;

  if (start_off > file->inode->size)
    start_off = file->inode->size;
  save = buflen;
  allocate_needed_blocks(file, start_off, buflen);
  while (buflen)
    {
      block = file_off_to_block(file, start_off, &block_off);
      if (!block)
	break;
      if (block_off)
	read_block(block, data);
      range = block_off ? BLOCK_SIZE - block_off : BLOCK_SIZE;
      copy = range > buflen ? buflen : range;
      kmemcpy(data + block_off, buf, copy);
      write_block(block, data);
      start_off += copy;
      buf += copy;
      buflen -= copy;
    }
  file->inode->size += save - buflen;
  write_inode(gl_hdd, file->inode_num, file->inode);
  return (save - buflen);
}
