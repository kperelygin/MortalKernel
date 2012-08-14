/*
** my_memcpy.c for mk in /home/mk/duc_l_mk/Kernel/src/lib
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Wed Feb  4 22:31:22 2009 Mortal Kernel
** Last update Wed Feb  4 23:36:39 2009 Mortal Kernel
*/

void	*kmemcpy(void *dst, void *src, int size)
{
  char	*d;
  char	*p;
  void	*pp;

  p = src;
  pp = dst;
  d = dst;
  while (size-- != 0)
    *d++ = *p++;
  return (pp);
}
