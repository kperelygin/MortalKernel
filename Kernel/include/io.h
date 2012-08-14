/*
** io.h for io in /home/mk/duc_l_mk/Kernel/include
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Mon Feb  2 23:31:53 2009 Mortal Kernel
** Last update Thu Feb 19 17:21:28 2009 Duc Lionel
*/

#ifndef __IO_H__
# define __IO_H__

/*
** Ensemble de macros en inline asm. Communications
** avec les controleurs de la carte mere.
*/

/*
** STore et CLear l'interruption flag
*/
# define STI() asm("sti"::)
# define CLI() asm("cli"::)

/*
** Lit un port (8b)
*/
# define inb(port) ({						\
      unsigned char _v;						\
      asm volatile ("inb %%dx, %%al" : "=a" (_v) : "d" (port)); \
      _v;							\
    })

/*
** Ecrit sur un port (8b)
*/
# define outb(port,value) asm volatile ("outb %%al, %%dx" :: "d" (port), "a" (value))

/*
** Ecrit puis jump (temps d'attente) (8b)
*/
# define outbp(port,value) asm volatile ("outb %%al, %%dx; jmp 1f; 1:" :: "d" (port), "a" (value))

/*
** Ecrit sur un port (16b)
*/
#define outw(port,value) asm volatile ("outw %%ax, %%dx" :: "d" (port), "a" (value))


/*
** Lit un port (16b)
*/
#define inw(port) ({						\
      u16 _v;							\
      asm volatile ("inw %%dx, %%ax" : "=a" (_v) : "d" (port));	\
      _v;							\
    })





#endif /*__IO_H__*/
