/*
** my_revstr.c for my3 in /u/all/duc_l/cu/rendu/lib/my3
** 
** Made by lionel duc
** Login   <duc_l@epitech.net>
** 
** Started on  Sun Sep 28 10:57:45 2008 lionel duc
** Last update Wed Feb  4 23:37:33 2009 Mortal Kernel
*/

char	*krevstr(char *str)
{
  int	i;
  int	n;
  int	mid;
  char	swap;

  i = 0;
  n = 0;
  while (str[i] != '\0')
    i++;
  mid = i / 2;
  i--;
  while (n < mid)
    {
      swap = str[n];
      str[n] = str[i];
      str[i] = swap;
      n++;
      i--;
    }
  return (str);
}
