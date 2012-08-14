/*
** main.c for mk in /home/mk/duc_l_mk/Kernel/src
** 
** Made by Mortal Kernel
** Login   <mk@epitech.net>
** 
** Started on  Tue Feb  3 00:52:19 2009 Mortal 
** Last update Sat Jul 11 03:24:44 2009 Duc Lionel
*/

#include <io.h>
#include <screen.h>
#include "libkern.h"
#include "interrupts.h"
#include "phy_mem.h"
#include "gdt.h"
#include "ata.h"
#include "vmem.h"
#include "fs.h"
#include "malloc.h"
#include "task.h"
#include "syscall.h"

/*
** Point d'entree du Kernel.
*/

t_task		*gl_tasklist = NULL;
t_task		*gl_current_task = NULL;
t_page_dir	*kdir;

u32		initial_ebp;
u32		initial_esp;

void	kmain();

void	_start()
{
  asm volatile("mov %%ebp, %0" : "=r" (initial_ebp));
  asm volatile("mov %%esp, %0" : "=r" (initial_esp));
  textattr = 0x07;
  vga_clear_screen();
  kprintf("\t\t-- Kernel loaded at 0x2000 -- size ~= 40 KB\n");
  kmain();
  while (1);
}

void	kmain()
{
  t_hdd	*hdd;
  u32	pid;

  create_gdt();
  textattr = TEXTATTR(BLACK, LGREY);
  kprintf(" * Loading new GDT...\t\t\t");
  textattr = TEXTATTR(BLACK, GREEN);
  kprintf("[Done]\n");

  pmem_init();
  textattr = TEXTATTR(BLACK, LGREY);
  kprintf(" * Loading Low-level Memory Manager...\t");
  textattr = TEXTATTR(BLACK, GREEN);
  kprintf("[Done]\n");
  textattr = TEXTATTR(BLACK, LGREY);

  create_idt();
  textattr = TEXTATTR(BLACK, LGREY);
  kprintf(" * Loading IDT...\t\t\t");
  textattr = TEXTATTR(BLACK, GREEN);
  kprintf("[Done]\n");

  reload_pic();
  textattr = TEXTATTR(BLACK, LGREY);
  kprintf(" * Programming PIC...\t\t\t");
  textattr = TEXTATTR(BLACK, GREEN);
  kprintf("[Done]\n");

  textattr = TEXTATTR(BLACK, LGREY);
  kprintf(" * Enabling Interrupts...\t\t");
  textattr = TEXTATTR(BLACK, GREEN);
  kprintf("[Done]\n");

  init_pit(50);
  textattr = TEXTATTR(BLACK, LGREY);
  kprintf(" * Initializing PIT (50Hz)...\t\t");
  textattr = TEXTATTR(BLACK, GREEN);
  kprintf("[Done]\n");

  kdir = init_paging(DEFAULT_MEM_SIZE);
  textattr = TEXTATTR(BLACK, LGREY);
  kprintf(" * Pagination Enabled...\t\t");
  textattr = TEXTATTR(BLACK, GREEN);
  kprintf("[Done]\n");

  textattr = TEXTATTR(BLACK, LGREY);
  kprintf(" * Initializing filesystem... \t\t");
  hdd = init_fs();
  init_vfs();
  textattr = TEXTATTR(BLACK, GREEN);
  kprintf("[Done]\n");

  mount(gl_vfs, "/", hdd);
  STI();

  textattr = TEXTATTR(BLACK, LGREY);
  kprintf(" * Initializing kernel task... \t\t");
  init_kernel_task();
  textattr = TEXTATTR(BLACK, GREEN);
  kprintf("[Done]\n");
  textattr = TEXTATTR(BLACK, LGREY);
  pid = kfork();
  if (pid == 0)
    {
      kprintf("Invoking shell...\n\n");
      sys_execve("/bin/mksh", NULL, NULL);
    }
  while (1);
}
