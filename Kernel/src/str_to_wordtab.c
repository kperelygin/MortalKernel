/*
** str_to_wordtab.c for broxy in /home/duc_l/baumga_j-broxy
** 
** Made by lionel duc
** Login   <duc_l@epitech.net>
** 
** Started on  Fri Jun 26 23:21:08 2009 lionel duc
** Last update Fri Jul 10 04:18:47 2009 Mortal Kernel
*/

#include "libkern.h"
#include "malloc.h"

int		countwords(char *s, char *sep)
{
  int		i;
  int		words;

  words = 0;
  i = 0;
  while (s[i])
    {
      if (i == 0 && !(kstrchr(sep, s[i])))
	words++;
      else if (i > 0 && !(kstrchr(sep, s[i])) && kstrchr(sep, s[i - 1]))
	words++;
      i++;
    }
  return (words);
}

char	**str_to_wordtab(char *s, char *separators)
{
  char	**tab;
  int	words;
  int	i;
  int	j;

  words = countwords(s, separators);
  tab = kmalloc(sizeof(*tab) * (words + 1));
  i = 0;
  while (i < words)
    {
      while (*s && kstrchr(separators, *s))
	s++;
      tab[i] = kmalloc(sizeof(*tab[i]) * (kstrlen(s) + 1));
      j = 0;
      while (*s && !(kstrchr(separators, *s)))
	{
	  tab[i][j] = *(s++);
	  j++;
	}
      tab[i][j] = 0;
      i++;
    }
  tab[i] = 0;
  return (tab);
}
