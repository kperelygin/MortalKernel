/*
** create_file.c for mk in /home/duc_l/duc_l_mk/Kernel
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Mon Jul  6 20:22:53 2009 Duc Lionel
** Last update Sat Jul 11 01:54:54 2009 Duc Lionel
*/

#include "fs.h"
#include "libkern.h"
#include "task.h"
#include "malloc.h"

t_node		*get_dir(char *path)
{
  t_node	*dir;
  int		i;

  i = kstrlen(path);
  if (!i)
    return (NULL);
  i--;
  while (i >= 0 && path[i] != '/')
    i--;
  if (i == -1)
    return (gl_current_task->cwd);
  path[i] = 0;
  dir = path_to_node(gl_vfs, path);
  path[i] = '/';
  return (dir);
}

t_node		*create_file(char *path, int mode)
{
  struct s_ext2_direntry dirent;
  t_node	*dir;
  t_node	*new;
  int		i;

  if (!(dir = get_dir(path)))
    return (NULL);
  new = kmalloc(sizeof(*new));
  i = kstrlen(path);
  while (i >= 0 && path[i] != '/')
    i--;
  new->filename = kstrdup(path + i + 1);
  new->cont = NULL;
  new->parent = dir;
  if (!(new->inode_num = alloc_inode(gl_hdd)))
    {
      kfree(new->filename);
      kfree(new);
      return (NULL);
    }
  new->inode = kmalloc(sizeof(*new->inode));
  kmemset(new->inode, 0, sizeof(*new->inode));
  new->inode->mode = mode;
  new->inode->mode |= EXT2_S_IFREG;
  new->inode->size = 0;
  write_inode(gl_hdd, new->inode_num, new->inode);
  //l'ajouter au repertoire
  dirent.inode = new->inode_num;
  dirent.rec_len = 0;
  dirent.name_len = kstrlen(new->filename);
  dirent.file_type = EXT2_FT_REG_FILE;
  kmemcpy(dirent.name, new->filename, dirent.name_len);
  add_direntry(gl_hdd, dir->inode, &dirent);
  //update le vfs
  add_in_list(&dir->cont, new);
  return (new);
}
