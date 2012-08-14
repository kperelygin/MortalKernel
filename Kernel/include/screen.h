/*
** screen.h for screen in /home/mk/duc_l_mk/Kernel/include
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Mon Feb  2 23:27:12 2009 Mortal Kernel
** Last update Wed Feb  4 22:21:57 2009 Mortal Kernel
*/

#ifndef __SCREEN_H__
# define __SCREEN_H__

# include <ctypes.h>

/*
** Ce fichier contient les sctructures et fonctions
** relatives au driver de l'ecran
*/

# define VGA_RAM	0xB8000
# define VGA_LIMIT	0xB8FA0
# define SCREEN_WIDTH	80
# define SCREEN_HEIGHT	25
# define SCREEN_SIZE	SCREEN_WIDTH * SCREEN_HEIGHT * 2 /* 80 * 25 * 2 */

# define TEXTATTR(bg, fg) (((bg) << 4) | ((fg) & 0x0F))

extern int	curs_row;
extern int	curs_col;
extern u8	textattr;

enum	e_vgargb
  {
    BLACK = 0x0,
    BLUE = 0x1,
    GREEN = 0x2,
    CYAN = 0x3,
    RED = 0x4,
    MAGENTA = 0x5,
    BROWN = 0x6,
    LGREY = 0x7,
    DGREY = 0x8,
    LBLUE = 0x9,
    LGREEN = 0xA,
    LCYAN = 0xB,
    ORANGE = 0xC,
    PINK = 0xD,
    LBROWN = 0xE,
    WHITE = 0xF
  };

void	vga_update_cursor(u8 col, u8 row);
void	vga_out_char(u8 c);
void	vga_scroll_up(int lines);
void	vga_clear_screen();
void	vga_putstr(char *s);

#endif /*__SCREEN_H__*/
