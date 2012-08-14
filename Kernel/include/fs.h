/*
** fs.h for mk in /home/duc_l/duc_l_mk/Kernel/src/fs
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Thu Mar 12 10:28:43 2009 Duc Lionel
** Last update Fri Jul 10 14:28:03 2009 Duc Lionel
*/

#ifndef __FS_H__
# define __FS_H__

# include "ext2.h"
# include "ata.h"
# include "libkern.h"

# define DEFAULT_BUS	ATA_PRIM_BUS
# define DEFAULT_DRIVE	0

# define BLOCK_SIZE	1024
# define SECT_PER_BLOCK	2

# define INODES_PER_BLOCK ((BLOCK_SIZE / sizeof(struct s_ext2_inode)))

# define SECT_TO_BLOCK(s) ((s) / SECT_PER_BLOCK)
# define SECT_TO_OFF(s)   ((s) * BYTES_PER_SECTOR)
# define BLOCK_TO_SECT(b) ((b) * SECT_PER_BLOCK)
# define BLOCK_TO_OFF(b)  ((b) * BLOCK_SIZE)
# define OFF_TO_SECT(o)   ((o) / BYTES_PER_SECTOR)
# define OFF_TO_BLOCK(o)  ((o) / BLOCK_SIZE)

typedef struct		s_node
{
  char			*filename;
  u32			inode_num;
  struct s_ext2_inode	*inode;
  t_list		*cont;
  struct s_node		*parent;
}			t_node;

typedef struct		s_vfs
{
  int			type;
  t_node		*root;
}			t_vfs;

typedef struct			s_hard_disk_drive
{
  u32				bus;
  int				master;
  struct s_ext2_superblock	*sb;
  struct s_ext2_bgd_entry	*gdt;
}				t_hdd;

typedef struct	s_open_file
{
  t_node	*file;
  int		offset; //current file pointer
  int		flags; //flags : r/w block etc...
  //write_function
  //read_function
  // functions for read/write allow us to open other things than files
}		t_open_file;

struct stat {
  u32		st_ino;		/* inode's number */
  int		st_mode;	/* inode protection mode */
  u32		st_nlink;	/* number of hard links */
  u32		st_uid;		/* user ID of the file's owner */
  u32		st_gid;		/* group ID of the file's group */

  int		st_atime;	/* time of last access */
  int		st_mtime;	/* time of last data modification */
  int		st_ctime;	/* time of last file status change */

  u64		st_size;	/* file size, in bytes */
  u32		st_blocks;	/* blocks allocated for file */
  int		st_blksize;	/* optimal blocksize for I/O */
  int		st_flags;	/* user defined flags for file */
  u32		st_gen;		/* file generation number */
};

extern t_vfs		*gl_vfs;
extern t_hdd		*gl_hdd;

int	mount(t_vfs *vfs, char *path, t_hdd *hdd);
int	read_file(t_node *file, u64 offset, void *buf, u32 buflen);
int	write_file(t_node *file, u64 start_off, void *buf, int buflen);

t_node	*path_to_node(t_vfs *vfs, char *path);

int	read_block(u32 blocknum, void *data);
int	read_inode(t_hdd *dd, u32 inum, struct s_ext2_inode *dst);
int	write_block(u32 blocknum, void *data);
void	write_inode(t_hdd *hdd, u32 inum, struct s_ext2_inode *ino);

t_vfs	*init_vfs(void);
t_hdd	*init_fs(void);
int	disk_read(int start_sector, void *buff, u32 readlen);
int	disk_write(int start_sector, void *buff, u32 readlen);

void	remove_direntry(t_hdd *hdd, struct s_ext2_inode *dirino,
		       struct s_ext2_direntry *entry);
void	release_inode(t_hdd *hdd, u32 inum);
void	release_block(t_hdd *hdd, u32 blocknum);
void	add_direntry(t_hdd *hdd, struct s_ext2_inode *dirino,
		     struct s_ext2_direntry *entry);
u32	alloc_block(t_hdd *hdd);
u32	alloc_inode(t_hdd *hdd);

int	file_off_to_block(t_node *file, u64 offset, int *remain);
int	blocknum_to_absblock(t_node *file, int blocknum);

int	indirect_level(int block);

t_node	*create_file(char *path, int mode);

char	*resolve_relative_path(t_node *n, char *path);
#endif
