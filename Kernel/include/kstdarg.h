/*
** kstdarg.h for mk in /home/mk/duc_l_mk/Kernel/src/lib
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Thu Feb  5 00:36:03 2009 Mortal Kernel
** Last update Thu Feb  5 00:36:03 2009 Mortal Kernel
*/

#ifndef __KSTDARG_H__
# define	__KSTDARG_H_

# ifdef __GNUCLIKE_BUILTIN_VARARGS
typedef __builtin_va_list	__va_list;	/* internally known to gcc */
# else
typedef	char *			__va_list;
#  endif /* __GNUCLIKE_BUILTIN_VARARGS */
# if defined(__GNUC_VA_LIST_COMPATIBILITY) && !defined(__GNUC_VA_LIST) \
    && !defined(__NO_GNUC_VA_LIST)
#  define __GNUC_VA_LIST
typedef __va_list		__gnuc_va_list;	/* compatibility w/GNU headers*/
# endif

# ifndef _VA_LIST_DECLARED
#  define	_VA_LIST_DECLARED
typedef	__va_list	va_list;
# endif

# define	va_start(ap, last) __builtin_va_start((ap), (last))
# define	va_arg(ap, type) __builtin_va_arg((ap), type)
# define	va_copy(dest, src) __builtin_va_copy((dest), (src))
# define	va_end(ap) __builtin_va_end(ap)

#endif /* __KSTDARG_H__ */
