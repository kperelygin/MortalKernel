/*
** my_strcmp.c for my3 in /u/all/duc_l/cu/rendu/lib/my3
** 
** Made by lionel duc
** Login   <duc_l@epitech.net>
** 
** Started on  Sat Sep 27 19:04:49 2008 lionel duc
** Last update Wed Feb  4 23:37:42 2009 Mortal Kernel
*/

int	kstrcmp(const char *s1, const char *s2)
{
  while (*s1 == *(s2++))
    {
      if (!*(s1++))
	return (0);
    }
  return (*s1 - *(s2 - 1));
}

int	kstrncmp(const char *s1, const char *s2, unsigned int len)
{
  if (!len)
    return (0);
  do
    {
      if (*s1 != *(s2++))
	return (*s1 - *(s2 - 1));
      if (!*(s1++))
	break;
    }
  while (--len != 0);
  return (0);
}
