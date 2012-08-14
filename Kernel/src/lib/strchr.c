/*
** strchr.c for mk in /home/duc_l/duc_l_mk/Kernel/src
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Fri Jul 10 14:49:27 2009 Duc Lionel
** Last update Fri Jul 10 14:51:36 2009 Duc Lionel
*/

#include "libkern.h"
#include "null.h"

char	*kstrchr(const char *s, int c)
{
  while (s && *s)
    {
      if (*s == c)
	return ((char *)s);
      s++;
    }
  return (NULL);
}
