/*
** sys_stat.c for mk in /home/duc_l/duc_l_mk/Kernel/src/syscalls
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Thu Jul  9 00:15:31 2009 Duc Lionel
** Last update Sat Jul 11 01:54:59 2009 Duc Lionel
*/

#include "task.h"
#include "syscall.h"
#include "fs.h"

int		sys_stat(const char *path, struct stat *sb)
{
  t_node	*f;
  const char	*realpath;

  if (path[0] != '/')
    realpath = resolve_relative_path(gl_current_task->cwd, (char *)path);
  else
    realpath = path;
  f = path_to_node(gl_vfs, (char *)realpath);
  if (!f)
    return (-1);
  sb->st_ino = f->inode_num;
  sb->st_mode = f->inode->mode;
  sb->st_nlink = f->inode->links_num;
  sb->st_uid = f->inode->uid;
  sb->st_gid = f->inode->gid;
  sb->st_atime = f->inode->last_access;
  sb->st_mtime = f->inode->last_modif;
  sb->st_ctime = f->inode->create;
  sb->st_size = f->inode->size;
  sb->st_blocks = f->inode->blocks;
  sb->st_blksize = BLOCK_SIZE;
  sb->st_flags = 0;
  sb->st_gen = f->inode->generation;
  return (0);
}
