/*
** libkern.h for mk in /home/mk/duc_l_mk/Kernel/src/lib
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Wed Feb  4 23:36:04 2009 Mortal Kernel
** Last update Fri Jul 10 15:32:11 2009 Duc Lionel
*/

#ifndef __LIBKERN_H__
# define __LIBKERN_H__

# define _HEXA "0123456789ABCDEF"

typedef struct		s_list
{
  void			*data;
  struct s_list		*next;
}			t_list;

typedef struct		s_dlist
{
  void			*data;
  struct s_dlist	*next;
  struct s_dlist	*prev;
}			t_dlist;

int	countwords(char *s, char *sep);
char	**str_to_wordtab(char *s, char *separators);

void	add_in_list(t_list **list, void *data);
void	add_in_dlist(t_dlist **list, void *data);
void	cat_to_list(t_list **list, void *data);

void	*kmemcpy(void *dst, void *src, int size);
void	*kmemset(void *b, int c, unsigned int len);
void	kputnbr(int n);
void	kputnbr_base(unsigned int n, char *base);
void	kputstr(char *str);
void	kputchar(char c);
char	*krevstr(char *str);
int	kstrcmp(const char *s1, const char *s2);
int	kstrncmp(const char *s1, const char *s2, unsigned int len);
int	kstrlen(char *str);

void	kprintf(char *fmt, ...);
int	ksprintf(char * __restrict str, char *fmt, ...); /*%d %i %c %s %x only*/

char	*kstrdup(char *s);
char	*kstrchr(const char *s, int c);

void	add_in_list(t_list **list, void *data);
void	add_in_dlist(t_dlist **list, void *data);
void	rm_from_list(t_list **begin, t_list *to_kill,
		     void (*data_destructor)());
void	rm_from_dlist(t_dlist **begin, t_dlist *to_kill,
		      void (*data_destructor)());

#endif /*__LIBKERN_H__*/
