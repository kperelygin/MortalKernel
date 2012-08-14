/*
** syscall.h for mk in /home/duc_l/duc_l_mk/Kernel/include
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Fri Jul  3 14:43:18 2009 Duc Lionel
** Last update Sat Jul 11 03:15:53 2009 Duc Lionel
*/

#ifndef __SYSCALL_H__
# define __SYSCALL_H__

# include "fs.h"

# define	SW_INTNUM	0x80

# define	SYS_syscall	0
# define	SYS_exit	1
# define	SYS_fork	2
# define	SYS_read	3
# define	SYS_write	4
# define	SYS_open	5
# define	SYS_close	6
# define	SYS_waitpid	7
# define	SYS_unlink	8
# define	SYS_chdir	9
# define	SYS_lseek	10
# define	SYS_execve      11
# define	SYS_getpid	12
# define	SYS_stat	13
# define	SYS_sbrk	14
# define	SYS_cwd		15
# define	SYS_MAXSYSCALL	16

# define	SYS_dbgprocs	42

# define	O_NONBLOCK	0x0004		/* no delay */
# define	O_APPEND	0x0008		/* set append mode */
# define	O_NOFOLLOW	0x0100		/* don't follow symlinks */
# define	O_CREAT		0x0200		/* create if nonexistent */
# define	O_TRUNC		0x0400		/* truncate to zero length */
# define	O_EXCL		0x0800		/* error if already exists */
# define	O_RDONLY	0x0000		/* open for reading only */
# define	O_WRONLY	0x0001		/* open for writing only */
# define	O_RDWR		0x0002		/* open for reading and writing */
# define	O_ACCMODE	0x0003		/* mask for above modes */

# define	SEEK_SET	0
# define	SEEK_CUR	1
# define	SEEK_END	2

# define	WNOHANG		1	/* Don't hang in wait. */
# define	WUNTRACED	2	/* Tell about stopped, untraced children. */
# define	WSTOPPED	WUNTRACED   /* SUS compatibility */
# define	WCONTINUED	4	/* Report a job control continued process. */
# define	WNOWAIT		8	/* Poll only. Don't delete the proc entry. */



int	sys_open(const char *, int, ...);
int	sys_read(const int fd, void *buf, int len);
int	sys_write(const int fd, void *buf, int len);
int	sys_close(int fd);
int	sys_execve(const char *path, char **argv, char **env);
int	sys_fork(void);
int	sys_exit(int n);
int	sys_getpid();
int	sys_stat(const char *path, struct stat *sb);
void	*sys_sbrk(int incr);
int	sys_chdir(const char *path);
int	sys_lseek(int , int , int);
int	sys_waitpid(int pid, int *status, int options);
int	sys_stat(const char *path, struct stat *sb);
int	sys_cwd(char *path);
int	sys_dbgprocs(void);

#endif
