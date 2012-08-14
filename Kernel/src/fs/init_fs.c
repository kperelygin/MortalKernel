/*
** init_fs.c for mk in /home/duc_l/duc_l_mk/Kernel/src/fs
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Thu Mar 12 10:27:57 2009 Duc Lionel
** Last update Tue Jul  7 00:21:42 2009 Duc Lionel
*/

#include "libkern.h"
#include "fs.h"
#include "io.h"
#include "malloc.h"

t_vfs		*gl_vfs;
t_hdd		*gl_hdd;

t_vfs		*init_vfs()
{
  t_vfs		*vfs;
  t_node	*root;

  vfs = kmalloc(sizeof(*vfs));
  vfs->type = EXT2_MAGIC;
  vfs->root = NULL;
  root = kmalloc(sizeof(*root));
  root->cont = NULL;
  root->parent = NULL;
  vfs->root = root;
  gl_vfs = vfs;
  return (vfs);
}

t_hdd		*init_fs()
{
  t_hdd		*master;

  master = kmalloc(sizeof(*master));
  master->sb = kmalloc(sizeof(*(master->sb)));
  master->bus = DEFAULT_BUS;
  master->master = 1;
  ata_select_drive(DEFAULT_BUS, 1);
  kmemset(master->sb, 0, EXT2_SUPER_BLOCK_SIZE);
  disk_read(EXT2_SUPER_BLOCK_BASE / BYTES_PER_SECTOR,
	    master->sb, EXT2_SUPER_BLOCK_SIZE);
  master->gdt = kmalloc(sizeof(*(master->gdt)) *
			(master->sb->s_blocks_count / master->sb->s_blocks_per_group));
  disk_read(OFF_TO_SECT(EXT2_BGD_BASE), master->gdt,
	    sizeof(*(master->gdt)) * EXT2_MAX_BGD_ENTRIES);
  gl_hdd = master;
  return (master);
}
