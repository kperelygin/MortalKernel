/*
** ext2_write.c for mk in /home/duc_l/duc_l_mk/Kernel/src/fs
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Tue Jun 30 12:00:51 2009 Duc Lionel
** Last update Sat Jul 11 01:37:45 2009 Duc Lionel
*/

#include "libkern.h"
#include "fs.h"

u32	alloc_inode(t_hdd *hdd)
{
  int	group;
  char	block[BLOCK_SIZE];
  int	i;
  int	j;
  int	test;

  for (group = 0; hdd->gdt[group].inode_bitmap &&
	 hdd->gdt[group].free_inodes_num == 0; group++);
  if (hdd->gdt[group].inode_bitmap == 0)
    {
      return (0);
    }
  read_block(hdd->gdt[group].inode_bitmap, block);
  j = 0;
  for (i = 0; i < BLOCK_SIZE && i * 8 + j < (int)hdd->sb->s_inodes_per_group; i++)
    for (j = 0; j < 8; j++)
      {
	test = 1 << (7 - j);
	if ((block[i] & test) == 0)
	  {
	    block[i] |= test;
	    write_block(hdd->gdt[group].inode_bitmap, block);
	    hdd->gdt[group].free_inodes_num--;
	    disk_write(OFF_TO_SECT(EXT2_BGD_BASE), hdd->gdt,
	          sizeof(*(hdd->gdt)) * EXT2_MAX_BGD_ENTRIES);
	    return ((i * 8 + j + hdd->sb->s_inodes_per_group * group) + 1);
	  }
      }
  return (0);
}

u32	alloc_block(t_hdd *hdd)
{
  int	group;
  char	block[BLOCK_SIZE];
  int	i;
  int	j;
  int	test;

  for (group = 0; hdd->gdt[group].block_bitmap &&
	 hdd->gdt[group].free_blocks_num == 0; group++);
  if (hdd->gdt[group].block_bitmap == 0)
    return (0);
  read_block(hdd->gdt[group].block_bitmap, block);
  for (i = 0; i < BLOCK_SIZE && i * 8 + j < (int)hdd->sb->s_blocks_per_group; i++)
    for (j = 0; j < 8; j++)
      {
	test = 1 << j;
	if ((block[i] & test) == 0)
	  {
	    block[i] |= test;
	    write_block(hdd->gdt[group].block_bitmap, block);
	    return (group * hdd->sb->s_blocks_per_group + 3 + (i * 8 + j));
	  }
      }
  return (0);
}

void			add_direntry(t_hdd *hdd, struct s_ext2_inode *dirino,
				     struct s_ext2_direntry *entry)
{
  u32			b;
  int			i;
  char			block[BLOCK_SIZE];
  struct s_ext2_direntry *tmp;
  int			gap;

  for (b = 0; b < dirino->blocks && dirino->block[b]; b++)
    {
      read_block(dirino->block[b], block);
      for (i = 0; i < BLOCK_SIZE; i += tmp->rec_len)
	{
	  tmp = (struct s_ext2_direntry *)(block + i);
	  gap = tmp->rec_len - EXT2_DIRENT_SZ(tmp);
	  if (gap > EXT2_DIRENT_SZ(entry))
	    {
	      entry->rec_len = gap;
	      tmp->rec_len = EXT2_DIRENT_SZ(tmp);
	      tmp = (struct s_ext2_direntry *)(block + i + tmp->rec_len);
	      kmemcpy(tmp, entry, EXT2_DIRENT_SZ(entry));
	      write_block(dirino->block[b], block);
	      return;
	    }
	}
    }
  hdd = hdd;//if here, allocate a new block ...
}

void	release_block(t_hdd *hdd, u32 blocknum)
{
  int	group;
  int	byte;
  int	bit;
  char	block[BLOCK_SIZE];

  group = blocknum / hdd->sb->s_blocks_per_group;
  blocknum = blocknum % hdd->sb->s_blocks_per_group;
  byte = blocknum / 8;
  bit = blocknum % 8;
  read_block(hdd->gdt[group].block_bitmap, block);
  block[byte] &= ~(1 << (7 - bit));
  write_block(hdd->gdt[group].block_bitmap, block);
}

void	release_inode(t_hdd *hdd, u32 inum)
{
  u8	block[BLOCK_SIZE];
  int	group;
  int	bit;
  int	byte;

  group = inum / hdd->sb->s_inodes_per_group;
  inum = inum % hdd->sb->s_inodes_per_group;
  byte = inum / 8;
  bit = inum % 8;
  read_block(hdd->gdt[group].inode_bitmap, block);
  block[byte] &= ~(1 << (7 - bit));
  write_block(hdd->gdt[group].inode_bitmap, block);
}

void			write_inode(t_hdd *hdd, u32 inum, struct s_ext2_inode *ino)
{
  int			group;
  u8			data[BLOCK_SIZE];

  inum--;
  group = inum / hdd->sb->s_inodes_per_group;
  inum = inum % hdd->sb->s_inodes_per_group;
  read_block(hdd->gdt[group].inode_table + (inum / INODES_PER_BLOCK), data);
  kmemcpy(data + ((inum % INODES_PER_BLOCK) * sizeof(*ino)), ino, sizeof(*ino));
  write_block(hdd->gdt[group].inode_table + (inum / INODES_PER_BLOCK), data);
}

int	write_block(u32 blocknum, void *data)
{
  return (disk_write(BLOCK_TO_SECT(blocknum), data, BLOCK_SIZE));
}
