/*
** read_file.c for mk in /home/duc_l/duc_l_mk/Kernel/src
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Tue Jun 30 07:52:18 2009 Duc Lionel
** Last update Sat Jul 11 01:41:23 2009 Duc Lionel
*/

#include "ctypes.h"
#include "libkern.h"
#include "fs.h"

int		indirect_level(int block)
{
  if (block < 12)
    return (0);
  if (block < 12 + (BLOCK_SIZE / 4))
    return (1);
  if (block < 12 + (BLOCK_SIZE / 4) + ((BLOCK_SIZE / 4) * (BLOCK_SIZE / 4)))
    return (2);
  return (3);
}

static int	indirect_blocknum(t_node *file, int blocknum)
{
  char		block[BLOCK_SIZE];
  int		*field;

  if (!file->inode->block[12])
    return (0);
  read_block(file->inode->block[12], block);
  blocknum -= 12; //12th block of the file is the 0th pointed by block here
  field = (int *)block;
  return (field[blocknum]);
}

static int	double_indirect_blocknum(t_node *file, int blocknum)
{
  char		block[BLOCK_SIZE];
  char		block2[BLOCK_SIZE];
  int		*indir;
  int		*field;
  int		blocks_per_indir;
  int		indirblock;

  if (!file->inode->block[13])
    return (0);
  read_block(file->inode->block[13], block);
  indir = (int *)block;
  blocks_per_indir = BLOCK_SIZE / 4;
  blocknum -= 12 + blocks_per_indir; //we are beyond the first indirect block; the 0th blocknum should be the 1st block of the 1st indirection
  indirblock = blocknum / blocks_per_indir;
  read_block(indir[indirblock], block2);
  field = (int *)block2;
  indirblock = blocknum % blocks_per_indir;
  return (field[indirblock]);
}

static int	triple_indirect_blocknum(t_node *file, int blocknum)
{
  int		indir1[BLOCK_SIZE / 4];
  int		indir2[BLOCK_SIZE / 4];
  int		field[BLOCK_SIZE / 4];
  int		blocks_per_indir1;
  int		blocks_per_indir2;
  int		block1;
  int		block2;

  if (!file->inode->block[14]) 
    return (0);
  read_block(file->inode->block[14], indir1);
  blocks_per_indir1 = (BLOCK_SIZE / 4) * (BLOCK_SIZE / 4);
  blocks_per_indir2 = BLOCK_SIZE / 4;
  block1 = blocknum / blocks_per_indir1;
  read_block(indir1[block1], indir2);
  block2 = blocknum % blocks_per_indir1;
  read_block(indir2[block2], field);
  return (field[blocknum % blocks_per_indir2]);
}

int		blocknum_to_absblock(t_node *file, int blocknum)
{
  int		indir;

  indir = indirect_level(blocknum);
  if (indir == 0)
    return (file->inode->block[blocknum]);
  if (indir == 1)
    return (indirect_blocknum(file, blocknum));
  if (indir == 2)
    return (double_indirect_blocknum(file, blocknum));
  return (triple_indirect_blocknum(file, blocknum));
}

int		file_off_to_block(t_node *file, u64 offset, int *remain)
{
  int		block;

  if (offset > file->inode->size)
    return (0);
  block = offset / BLOCK_SIZE;
  if (remain)
    *remain = offset % BLOCK_SIZE;
  return (blocknum_to_absblock(file, block));
}

int	read_file(t_node *file, u64 offset, void *buf, u32 buflen)
{
  u32	block;
  int	block_off;
  int	read_datas;
  u8	data[BLOCK_SIZE];
  int	copy;
  int	range;
  int	a;

  if (!file)
    return (-1);
  read_datas = 0;
  while (buflen > 0 && offset < file->inode->size && (offset / BLOCK_SIZE) < file->inode->blocks)
    {
      block = file_off_to_block(file, offset, &block_off);
      if (!block)
	break;
      a = read_block(block, data);
      range = block_off ? BLOCK_SIZE - block_off : a;
      offset += range;
      if (offset < file->inode->size)
	copy = buflen < BLOCK_SIZE ? buflen : BLOCK_SIZE;
      else
	copy = buflen < file->inode->size - (offset - range) ? buflen : file->inode->size - (offset - range);
      kmemcpy(buf, data + block_off, copy);
      buf += copy;
      buflen -= copy;
      read_datas += copy;
    }
  return (read_datas);
}
