/*
** ext2.h for mk in /home/duc_l/duc_l_mk/Kernel/include
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Sat Feb 28 15:18:44 2009 Duc Lionel
** Last update Mon Jul  6 21:54:20 2009 Duc Lionel
*/

#ifndef __EXT2_H__
# define __EXT2_H__

# include "ctypes.h"

# define EXT2_SUPER_BLOCK_BASE	0x400 //1024
# define EXT2_SUPER_BLOCK_SIZE	0x400
# define EXT2_MAGIC		0xEF53
# define EXT2_REVISION		0
# define EXT2_BGD_BASE		0x800 //block 3
# define EXT2_MAX_BGD_ENTRIES	32

/* Structure superblock : cf. http://www.nongnu.org/ext2-doc/ext2.html#SUPERBLOCK */

struct	s_ext2_superblock
{
  u32	s_inodes_count;
  u32	s_blocks_count;
  u32	s_r_blocks_count; /*reserved blocks*/
  u32	s_free_blocks_count;
  u32	s_free_inodes_count;
  u32	s_first_data_block; /*== superblock id*/
  u32	s_log_block_size; /*real block size = 1024 << log_block_size */
  int	s_log_frag_size; /*if > 0 -> frag_size = 1024 << log_fragment_size (else >> -log_frag_size)*/
  u32	s_blocks_per_group;
  u32	s_frags_per_group;
  u32	s_inodes_per_group;

  int	s_mtime; /*timestamp, modif time*/
  int	s_wtime; /*timestamp, last write time*/
  u16	s_mnt_count; /*how many time the file system was mounted since the last time it was fully verified*/
  u16	s_max_mnt_count; /*if mount_num == max_mount_num -> total check !*/
  u16	s_magic;
  u16	s_state;
  u16	s_errors;
  u16	s_minor_rev_level;
  int	s_lastcheck; /*timestamp*/
  int	s_checkinterval;
  u32	s_creator_os; /* 0 = linux, 1 = hurd, 2 = masix, 3 = fbsd, 4 = lites, et nous ? :P*/
  u32	s_rev_level; /*ext2 version, 0 ou 1*/
  u16	s_def_resuid; /* user id pouvant ecrire et lire les reserved blocks */
  u16	s_def_resgid; /* gid pouvant ecrire et lire les reserved blocks */
  u32	s_first_ino; /*Premier inode non-reserve utilisable*/
  u16	s_inode_size; /* DOIT ETRE <= 1 << log_block_size*/
  u16	s_block_group_nr;

  u32	s_feature_compat; /*masque decrivant les features supportees*/
  u32	s_feature_incompat;
  u32	s_feature_ro_compat;
  u64	s_uuid[2]; /*volume id*/
  char	s_volume_name[16]; /*zero-end*/
  char	s_last_mounted[64]; /*zero-end*/
  u32	s_algo_bitmap;
  u8	s_prealloc_blocks;
  u8	s_prealloc_dir_blocks;
  u16	align;
  u8	s_journal_uuid[16];
  u32	s_journal_inum;
  u32	s_journal_dev;
  u32	s_last_orphan; /*number of the first inode of the list to delete*/
  u32	s_hash_seed[4];
  u8	s_def_hash_version;
  u8	padding[3];
  u32	s_default_mount_options;
  u32	s_first_meta_bg;
  u8	unused[768];
}__attribute__((packed));
/*
** Group descriptor table:
** The Group Descriptor Table contains an entry for each block
** group within the filesystem. The table is located in the
** block after the superblock.
** http://www.nongnu.org/ext2-doc/ext2.html#BLOCK-GROUP-DESCRIPTOR-TABLE
*/

struct	s_ext2_bgd_entry
{
  u32	block_bitmap;	/*first block of the block_bitmap for the group*/
  u32	inode_bitmap;	/*first block of the inode_bitmap*/
  u32	inode_table;	/*first block of the inode_table*/
  u16	free_blocks_num;
  u16	free_inodes_num;
  u16	dir_inodes_num; /*number of inodes allocated to directories*/
  u16	pad;
  char	reserved[12];
}__attribute__((packed));

struct	s_ext2_inode
{
  u16	mode;	/*see enum i_modes*/
  u16	uid;	/*file owner id*/
  u32	size;	/*size in bytes*/
  /*timestamps*/
  int	last_access;
  int	create;
  int	last_modif;
  int	delete;

  u16	gid;
  u16	links_num;	/*hard links number*/
  u32	blocks;		/*number of blocks used*/
  u32	flags;		/*see enum i_flags*/
  u32	osd1;
  u32	block[15];	/*blocks containing datas (zero-end)*/
  u32	generation;
  u32	acl;
  u32	dir_acl;
  u32	fragment_address;
  char	osd2[12];
}__attribute__((packed));

enum	ext2_i_modes
  {
    /*file type*/
    EXT2_S_IFSOCK = 0xC000,
    EXT2_S_IFLNK = 0xA000,
    EXT2_S_IFREG = 0x8000,
    EXT2_S_IFBLK = 0x6000,
    EXT2_S_IFDIR = 0x4000,
    EXT2_S_IFCHR = 0x2000,
    EXT2_S_IFIO = 0x1000,
    /*user/group override*/
    EXT2_S_ISUID = 0x0800,
    EXT2_S_IDGID = 0x0400,
    EXT2_S_ISVTX = 0x0200,
    /*rights*/
    EXT2_S_IRUSR = 0x0100,
    EXT2_S_IWUSR = 0x0080,
    EXT2_S_IXUSR = 0x0040,
    EXT2_S_IRGRP = 0x0020,
    EXT2_S_IWGRP = 0x0010,
    EXT2_S_IXGRP = 0x0008,
    EXT2_S_IROTH = 0x0004,
    EXT2_S_IWOTH = 0x0002,
    EXT2_S_IXOTH = 0x0001
  };

enum	ext2_i_flags
  {
    EXT2_SECRM_FL	= 0x00000001,
    EXT2_UNRM_FL	= 0x00000002,
    EXT2_COMPR_FL	= 0x00000004,
    EXT2_SYNC_FL	= 0x00000008,
    EXT2_IMMUTABLE_FL	= 0x00000010,
    EXT2_APPEND_FL	= 0x00000020,
    EXT2_NODUMP_FL	= 0x00000040,
    EXT2_NOATIME_FL	= 0x00000080,
    EXT2_DIRTY_FL	= 0x00000100,
    EXT2_COMPRBLK_FL	= 0x00000200,
    EXT2_NOCOMPR_FL	= 0x00000400,
    EXT2_ECOMPR_FL	= 0x00000800,
    EXT2_BTREE_FL	= 0x00010000,
    EXT2_INDEX_FL	= 0x00010000,
    EXT2_IMAGIC_FL	= 0x00020000,
    EXT3_JOURNAL_DATA_FL= 0x00040000,
    EXT2_RESERVED_FL	= 0x80000000
  };

# define EXT2_NAME_LEN 255

# define EXT2_FT_REG_FILE       1
# define EXT2_FT_DIR            2
# define EXT2_FT_CHRDEV		3
# define EXT2_FT_BLKDEV		4
# define EXT2_FT_SYMLINK	7

# define EXT2_DIRENT_SZ(n) (n->name_len + 8)

struct	s_ext2_direntry
{
  u32	inode;             /* Inode number */
  u16	rec_len;                /* Directory entry length */
  u8	name_len;               /* Name length */
  u8	file_type;		/* File type */
  char	name[EXT2_NAME_LEN];   /* File name */
}__attribute__((packed));

#endif /*!__EXT2_H__*/
