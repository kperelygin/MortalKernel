/*
** ata.h for mk in /home/duc_l/duc_l_mk/Kernel/src
** 
** Made by Duc Lionel
** Login   <duc_l@epitech.net>
** 
** Started on  Wed Feb 18 12:32:09 2009 Duc Lionel
** Last update Thu Mar 12 14:08:57 2009 Duc Lionel
*/

#ifndef __ATA_H__
# define __ATA_H__

# include "ctypes.h"

# define ATA_PRIM_BUS	0x1F0
# define ATA_SEC_BUS	0x170

# define BYTES_PER_SECTOR 512
/*
**  -- ATA CONTROLLER STATUS BYTE --
**
** Bit	Abbreviation	Function
**
** 7	BSY		Drive is preparing to accept/send data -- wait until this bit clears. If it never
**			clears, do a Software Reset. Technically, when BSY is set, the other bits in the
**			Status byte are meaningless.
** 6	RDY		Bit is clear when drive is spun down, or after an error. Set otherwise.
** 5	DF		Drive Fault Error (does not set ERR!)
** 4	SRV		Overlapped Mode Service Request
** 3	DRQ		Set when the drive has PIO data to transfer, or is ready to accept PIO data.
** 2	CORR		Data corrected.
** 1	IDX		Index mark.
** 0	ERR		Error flag (when set). Send a new command to clear it (or nuke it with a Software
**			Reset).
*/

/*
** -- ATA CONTROL REGISTER BITS --
**
** Bit	Abbreviation	Function
**
** 7	HOB		Set this to read back the High Order Byte of the last LBA48 value sent to an IO port.
** 2	SRST		Software Reset -- set this to reset all ATA drives on a bus, if one is misbehaving.
** 1	nIEN		Set this to stop the current device from sending interrupts.
**
*/

/*
** Le tableau ci dessous permet d'obtenir un port
** en additionnant l'adresse du bus a la valeur
** du port souhaite.
*/

typedef enum	e_ATA_PORTS
  {
    ATA_PIO_DATA = 0,
    ATA_ERR = 1,	/*read*/
    ATA_FEAT = 1,	/*write*/
    ATA_SECT_COUNT = 2,
    ATA_LBA_LOW = 3,
    ATA_LBA_MID = 4,
    ATA_LBA_HI = 5,
    ATA_DRIVE = 6,
    ATA_STATUS = 7,	/*read*/
    ATA_COM = 7,	/*write*/
    ATA_ALT_STATUS = 0x206, /*read*/
    ATA_DEV_CONTROL = 0x206 /*write*/
  }		t_ATA_PORTS;

typedef enum	e_ATA_CR
  {
    ERR = 0x01,
    IDX = 0x02,
    CORR = 0x04,
    DRQ = 0x08,
    SRV = 0x10,
    DF = 0x20,
    RDY = 0x40,
    BSY = 0x80
  }		t_ATA_CR;

typedef enum	e_ATA_COMMANDS
  {
    SELECT_MASTER = 0xA0,
    SELECT_SLAVE = 0xB0,
    IDENTIFY = 0xEC,
    READ_SECTORS = 0x20,
    WRITE_SECTORS = 0x30
  }		t_ATA_COMS;

extern int	gl_sel_master;
extern int	gl_sel_port;

int	ata_select_drive(int bus, int master); /*bus = ATA_PRIM_BUS ou ATA_SEC_BUS*/
int	ata_identify(int bus);
int	ata_write(int bus, int drive, int lba, u8 count, void *data, u32 len);
int	ata_read(int bus, int drive, int lba, u8 count, char *buff, u32 len);

#endif /*__ATA_H__*/
