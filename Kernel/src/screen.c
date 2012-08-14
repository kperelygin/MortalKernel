/*
** screen.c for screen in /home/mk/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Mon Feb  2 23:26:40 2009 Mortal Kernel
** Last update Thu Jul  9 04:54:34 2009 Duc Lionel
*/

#include <screen.h>
#include <io.h>

int	curs_row;
int	curs_col;
u8	textattr;

/*
** Cette fonction update le curseur Hardware de l'ecran
*/

void	vga_update_cursor(u8 col, u8 row)
{
  u16	offset;

  offset = row * SCREEN_WIDTH + col;
  outb(0x03D4, 0x0E);/*les bits de poids fort d'abord*/
  outb(0x03D5, (offset >> 8) & 0xFF); /*Si on ecrit 0x1234, ca serait 0x12*/
  outb(0x03D4, 0x0F);/*maintenant poids faible*/
  outb(0x03D5, offset & 0xFF); /*la ca serait 34*/
}

void	vga_scroll_up(int lines)
{
  u8	*vga;
  u8	*tmp;

  vga = (u8 *)VGA_RAM;
  while (vga < (u8 *)VGA_LIMIT)
    {
      tmp = vga + (lines * SCREEN_WIDTH * 2);
      if (tmp < (u8 *)VGA_LIMIT)
	{
	  *vga = *tmp;
	  if (tmp + 1 < (u8 *)VGA_LIMIT)
	    *(vga + 1) = *(tmp + 1);
	}
      else
	{
	  *vga = ' ';
	  *(vga + 1) = TEXTATTR(BLACK, LGREY);
	}
      vga++;
      vga++;
    }
  curs_row -= lines;
}

void	vga_out_char(u8 c)
{
  u16	offset;
  u8	*vga;

  if (c == '\n')
    {
      curs_col = 0;
      curs_row++;
    }
  else if (c == '\r')
    curs_col = 0;
  else if (c == '\b')
    {
      if (curs_col > 0)
	curs_col = curs_col - 1;
      else
	{
	  curs_row--;
	  curs_col = SCREEN_WIDTH - 1;
	}
      offset = curs_row * (SCREEN_WIDTH * 2) + (curs_col * 2);
      vga = (u8 *)VGA_RAM + offset;
      *vga = ' ';
      *(vga + 1) = textattr;
    }
  else if (c == '\t')
    curs_col = curs_col + 8 - (curs_col % 8);
  else
    {
      offset = curs_row * (SCREEN_WIDTH * 2) + (curs_col * 2);
      vga = (u8 *)VGA_RAM + offset;
      *vga = c;
      *(vga + 1) = textattr;
      curs_col++;
      if (curs_col > SCREEN_WIDTH - 1)
	{
	  curs_col = 0;
	  curs_row++;
	}
    }
  if (curs_row >= SCREEN_HEIGHT)
    vga_scroll_up(curs_row - (SCREEN_HEIGHT - 1));
  vga_update_cursor((u8)curs_col, (u8)curs_row);
}

void	vga_clear_screen()
{
  u8	*vga;

  vga = (u8 *)VGA_RAM;
  while (vga < (u8 *)VGA_LIMIT)
    {
      *vga = 0;
      vga++;
      *vga = 0x7;
      vga++;
    }
  curs_row = 0;
  curs_col = 0;
  vga_update_cursor(0, 0);
}

void	vga_putstr(char *s)
{
  while (*s)
    vga_out_char(*s++);
}
