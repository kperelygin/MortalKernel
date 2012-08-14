/*
** mount.c for mk in /home/duc_l/duc_l_mk/Kernel/src/fs
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Mon Jun 29 13:38:30 2009 Duc Lionel
** Last update Sat Jul 11 00:22:28 2009 Duc Lionel
*/

#include "libkern.h"
#include "malloc.h"
#include "screen.h"
#include "fs.h"

static int	mount_errs(t_node *p, char *path)
{
  if (!p)
    {
      kprintf("Cannot mount on %s, not found.\n", path);
      return (-1);
    }
  if (p->cont)
    {
      kprintf("Cannot mount on %s, not empty.\n", path);
      return (-1);
    }
  if (p->inode && (p->inode->mode & EXT2_S_IFDIR) != EXT2_S_IFDIR)
    {
      kprintf("Cannot mount on %s, not a directory.\n", path);
      return (-1);      
    }
  return (0);
}

static void		set_slash(t_node *p, t_hdd *dd)
{
  struct s_ext2_inode	root;

  read_inode(dd, 2, &root);
  p->filename = kstrdup("/");
  p->inode = kmalloc(sizeof(*p->inode));
  p->inode_num = 2;
  kmemcpy(p->inode, &root, sizeof(root));
  p->cont = NULL;
  p->parent = NULL;
}

static char	*get_filename(struct s_ext2_direntry *dirent)
{
  char		*s;

  s = kmalloc(sizeof(*s) * dirent->name_len + 1);
  kmemcpy(s, dirent->name, dirent->name_len);
  s[dirent->name_len] = 0;
  return (s);
}

static void			expand_vfs(t_node *node, t_hdd *hdd)
{
  struct s_ext2_direntry	*dirent;
  u8				block[BLOCK_SIZE];
  int				i;
  u32				b;
  t_node			*new;

  for (b = 0; b < node->inode->blocks && node->inode->block[b]; b++)
    {
      read_block(node->inode->block[b], block);
      for (i = 0; i < BLOCK_SIZE; i += dirent->rec_len)
	{
	  dirent = (struct s_ext2_direntry *)(block + i);
	  new = kmalloc(sizeof(*new));
	  cat_to_list(&node->cont, new);
	  new->filename = get_filename(dirent);
	  new->cont = NULL;
	  new->parent = node;
	  if (!kstrcmp(new->filename, "."))
	    {
	      new->inode = node->inode;
	      new->inode_num = node->inode_num;
	      new->cont = node->cont;
	      new->parent = node->parent;
	    }
	  else if (!kstrcmp(new->filename, ".."))
	    {
	      new->inode = (node->parent ? node->parent->inode : gl_vfs->root->inode);
	      new->inode_num = (node->parent ? node->parent->inode_num : gl_vfs->root->inode_num);
	      new->cont = (node->parent ? node->parent->cont : gl_vfs->root->cont);
	      new->parent = (node->parent ? node->parent->parent : NULL);
	    }
	  else
	    {
	      new->inode = kmalloc(sizeof(*new->inode));
	      new->inode_num = dirent->inode;
	      read_inode(hdd, dirent->inode, new->inode);
	    }
	  if (kstrcmp(new->filename, ".") && kstrcmp(new->filename, "..") &&
	      dirent->file_type == EXT2_FT_DIR)
	    {
	      expand_vfs(new, hdd);
	    }
	  if (dirent->rec_len == 0)
	    break;
	}
    }
}

int		mount(t_vfs *vfs, char *path, t_hdd *hdd)
{
  t_node	*p;

  p = path_to_node(vfs, path);
  if (mount_errs(p, path))
    return (-1);
  textattr = TEXTATTR(BLACK, LGREY);
  kprintf(" * Mounting hard disk on /... \t\t");
  set_slash(p, hdd);
  expand_vfs(p, hdd);
  textattr = TEXTATTR(BLACK, GREEN);
  kprintf("[Done]\n");
  textattr = TEXTATTR(BLACK, LGREY);
  return (0);
}
