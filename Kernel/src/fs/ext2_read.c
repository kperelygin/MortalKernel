/*
** ext2_read.c for ext2_read in /home/duc_l/duc_l_mk/Kernel
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Tue Jun 30 04:35:40 2009 Duc Lionel
** Last update Sat Jul 11 01:08:28 2009 Duc Lionel
*/

#include "libkern.h"
#include "ctypes.h"
#include "fs.h"

/*
** Data must be at least BLOCK_SIZE long
*/

int	read_block(u32 blocknum, void *data)
{
  return (disk_read(BLOCK_TO_SECT(blocknum), data, BLOCK_SIZE));
}

int		read_inode(t_hdd *dd, u32 inum, struct s_ext2_inode *dst)
{
  int		group;
  u8		data[BLOCK_SIZE];
  static int	inodes_per_block = 0;
  
  if (inodes_per_block == 0)
    inodes_per_block = BLOCK_SIZE / sizeof(struct s_ext2_inode);
  inum--;
  if (!inum)
    return (-1);
  group = inum / dd->sb->s_inodes_per_group;
  inum = inum % dd->sb->s_inodes_per_group;
  read_block(dd->gdt[group].inode_table + (inum / inodes_per_block), data);
  kmemcpy(dst, data + ((inum % inodes_per_block) * sizeof(*dst)), sizeof(*dst));
  return (0);
}
