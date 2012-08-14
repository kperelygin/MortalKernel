/*
** ata.c for mk in /home/duc_l/duc_l_mk/Kernel/src
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Wed Feb 18 12:23:25 2009 Duc Lionel
** Last update Sat Jul 11 01:25:35 2009 Duc Lionel
*/

#include "io.h"
#include "ata.h"
#include "libkern.h"

int	gl_sel_master = 0xFF;
int	gl_sel_port = 0xFF;

/*
** /!\ Master is drive 0 
*/

static int	ata_wait_dev(int port)
{
  u8	c;

  c = inb(port + ATA_STATUS);
  while ((c & BSY) && !(c & DRQ) && (c & ERR))
    c = inb(port);
  if (c & ERR)
    return (-1);
  return (0);
}

static void	ata_pre_io(int bus, int slavebit, int lba, u8 count)
{
  u8		com;

  com = (gl_sel_master ? 0xE0 : 0xF0);
  outb(bus + ATA_DRIVE, com | (slavebit << 4) | ((lba >> 24) & 0x0F));
  outb(bus + ATA_FEAT, 0x0);
  outb(bus + ATA_SECT_COUNT, count);
  outb(bus + ATA_LBA_LOW, (u8) lba & 0xFF);
  outb(bus + ATA_LBA_MID, (u8)((lba >> 8) & 0xFF));
  outb(bus + ATA_LBA_HI, (u8)((lba >> 16) & 0xFF));
}

int	ata_select_drive(int bus, int master)
{
  int	port;

  if (gl_sel_master == master && gl_sel_port == bus)
    return (0);
  CLI();
  port = bus + ATA_DRIVE;
  gl_sel_port = bus;
  gl_sel_master = master;
  if (master)
    outbp(port, SELECT_MASTER);
  else
    outbp(port, SELECT_SLAVE);
  /*400 ns*/
  inb(bus + ATA_ALT_STATUS);
  inb(bus + ATA_ALT_STATUS);
  inb(bus + ATA_ALT_STATUS);
  inb(bus + ATA_ALT_STATUS);
  STI();
  return (0);
}

int	ata_identify(int bus)
{
  int	port;
  int	i;
  u16	w;
  u8	c;
  char	*drive;
  char	*bus_name;
  u16	ident[256];

  CLI();
  port = bus + ATA_COM;
  outbp(port, IDENTIFY);
  c = inb(port);
  if (bus == ATA_PRIM_BUS)
    bus_name = "Primary bus";
  else
    bus_name = "Secondary bus";
  if (gl_sel_master)
    drive = "Master";
  else
    drive = "Slave";
  if (c == 0)
    {
      kprintf("Drive (%s/%s) does not exist.\n", bus_name, drive);
      return (-1);
    }
  if (ata_wait_dev(port) == -1)
    return (-1);
  port = bus + ATA_PIO_DATA;
  i = 0;
  while (i < 256)
    {
      w = inw(port);
      ident[i++] = w;
    }
  STI();
  return (0);
}

/*
** 28 bit LBA
*/
int	ata_write(__attribute__((unused))int bus, int drive,
		  int lba, u8 count, void *data, u32 len)
{
  u16 tmpword;
  int idx;
  int numblock = lba;
  u8	*buf = data;

  outb(0x1F1, 0x00);
  outb(0x1F2, count);
  outb(0x1F3, (unsigned char) numblock);
  outb(0x1F4, (unsigned char) (numblock >> 8));
  outb(0x1F5, (unsigned char) (numblock >> 16));
  outb(0x1F6, 0xE0 | (drive << 4) | ((numblock >> 24) & 0x0F));
  outb(0x1F7, 0x30);
  while (!(inb(0x1F7) & 0x08)); /*poll*/
  for (idx = 0; idx < 256 * count; idx++)
    {
      tmpword = (buf[idx * 2 + 1] << 8) | buf[idx * 2];
      outw(0x1F0, tmpword);
    }
  return (len);
}

/*
** 28 bit LBA
*/
int	ata_read(int bus, int drive, int lba, u8 count, char *buff, u32 len)
{
  int	i;
  u16	w;
  u32	j;
  int	ret;

  ret = 0;
  j = 0;
  CLI();
  ata_pre_io(bus, drive, lba, count);
  outb(bus + ATA_COM, READ_SECTORS);
  while (count)
    {
      while (ata_wait_dev(bus) != 0); /*poll*/
      i = 0;
      while (i < 256)
	{
	  w = inw(bus + ATA_PIO_DATA);
	  ret += 2;
	  if (j < len)
	    buff[j++] = w & 0xff;
	  if (j < len)
	    buff[j++] = w >> 8;
	  i++;
	}
      count--;
    }
  STI();
  return (ret);
}
