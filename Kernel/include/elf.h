/*
** elf.h for mk in /home/mk/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Thu Jul  9 23:54:21 2009 Mortal Kernel
** Last update Fri Jul 10 01:24:10 2009 Mortal Kernel
*/

#ifndef __ELF_H__
# define __ELF_H__

# include "ctypes.h"

typedef struct
{
  unsigned char e_ident[16];	/* ELF identification */
  u16 e_type;			/* 2 (exec file) */
  u16 e_machine;		/* 3 (intel architecture) */
  u32 e_version;		/* 1 */
  u32 e_entry;			/* starting point */
  u32 e_phoff;			/* program header table offset */
  u32 e_shoff;			/* section header table offset */
  u32 e_flags;			/* various flags */
  u16 e_ehsize;			/* ELF header (this) size */
  u16 e_phentsize;		/* program header table entry size */
  u16 e_phnum;			/* number of entries */
  u16 e_shentsize;		/* section header table entry size */
  u16 e_shnum;			/* number of entries */
  u16 e_shstrndx;		/* index of the section name string table */
} Elf32_Ehdr;

/*
 * PROGRAM HEADER
 */
typedef struct
{
  u32 p_type;			/* type of segment */
  u32 p_offset;
  u32 p_vaddr;
  u32 p_paddr;
  u32 p_filesz;
  u32 p_memsz;
  u32 p_flags;
  u32 p_align;
} Elf32_Phdr;

/*
 * ELF identification
 */
# define EI_MAG0	0
# define EI_MAG1	1
# define EI_MAG2	2
# define EI_MAG3	3
# define EI_CLASS	4
# define EI_DATA	5
# define EI_VERSION	6
# define EI_PAD		7

/* EI_MAG */
# define ELFMAG		00x7f
# define ELFMAG1	'E'
# define ELFMAG2	'L'
# define ELFMAG3	'F'

/* EI_CLASS */
# define ELFCLASSNONE	0	/* invalid class */
# define ELFCLASS32	1	/* 32-bit objects */
# define ELFCLASS64	2	/* 64-bit objects */

/* EI_DATA */
# define ELFDATANONE	0	/* invalide data encoding */
# define ELFDATA2LSB	1	/* least significant byte first (0x01020304 is 0x04 0x03 0x02 0x01) */
# define ELFDATA2MSB	2	/* most significant byte first (0x01020304 is 0x01 0x02 0x03 0x04) */

/* EI_VERSION */
# define EV_CURRENT	1
# define ELFVERSION	EV_CURRENT

/* p_type */
#define PT_NULL		0
#define PT_LOAD		1
#define PT_DYNAMIC	2
#define PT_INTERP	3
#define PT_NOTE		4
#define PT_SHLIB	5
#define PT_PHDR		6
#define PT_LOPROC	0x70000000
#define PT_HIPROC	0x7fffffff

void	*load_elf(t_node *file);

#endif /*!__ELF_H__*/
