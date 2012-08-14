/*
** vfs.c for mk in /home/duc_l/duc_l_mk/Kernel/src/fs
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Mon Jun 29 14:06:10 2009 Duc Lionel
** Last update Sat Jul 11 01:50:57 2009 Duc Lionel
*/

#include "fs.h"
#include "malloc.h"

static int	dirlen(char *s)
{
  char		*p;

  p = s;
  while (s && *s && *s != '/')
    s++;
  return (s - p);
}

static t_node	*path_to_node_rec(t_node *node, char *path)
{
  int		len;
  t_list	*n;
  t_node	*tmp;

  while (path && *path == '/')
    path++;
  len = dirlen(path);
  n = node->cont;
  while (n)
    {
      tmp = n->data;
      if (!kstrcmp(path, tmp->filename))
	return (tmp);
      if (kstrlen(tmp->filename) == len && !kstrncmp(tmp->filename, path, len))
	return (path_to_node_rec(tmp, path + len));
      n = n->next;
    }
  return (NULL);
}

t_node		*path_to_node(t_vfs *vfs, char *path)
{
  int		len;
  char		*s;
  t_node	*ret;

  while (path && *path == '/')
    path++;
  if (kstrlen(path) == 0)
    return (vfs->root);
  s = kstrdup(path);
  len = kstrlen(path);
  while (len > 1 && s[len - 1] == '/')
    s[--len] = 0;
  ret = path_to_node_rec(vfs->root, s);
  kfree(s);
  return (ret);
}
