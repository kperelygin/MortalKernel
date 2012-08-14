##
## Makefile for mk in /home/mk/duc_l_mk/Kernel
## 
## Made by Mortal Kernel
## Login   <mk@epitech.net>
## 
## Started on  Tue Feb  3 01:00:48 2009 Mortal Kernel
## Last update Sat Jul 11 03:21:48 2009 Duc Lionel
##

BASE_ADDR	=	2000

CSRCS	=	src/main.c \
		src/idt.c \
		src/gdt.c \
		src/pic.c \
		src/pit.c \
		src/ata.c \
		src/kfork.c \
		src/kexec.c \
		src/ktask.c \
		src/elf.c \
		src/vmem.c \
		src/screen.c \
		src/phy_mem.c \
		src/paging.c \
		src/dt_memory.c \
		src/task_list.c \
		src/fs/init_fs.c \
		src/fs/disk_read.c \
		src/interrupts.c \
		src/keyboard_map.c \
		src/str_to_wordtab.c \
		src/malloc/kfree.c \
		src/malloc/kmalloc.c \
		src/malloc/kmalloc_tools.c \
		src/fs/disk_write.c \
		src/fs/mount.c \
		src/fs/vfs.c \
		src/fs/ext2_read.c \
		src/fs/ext2_write.c \
		src/fs/read_file.c \
		src/fs/write_file.c \
		src/fs/create_file.c \
		src/fs/resolve_relative_path.c \
		src/syscalls/handle_syscalls.c \
		src/syscalls/sys_open.c \
		src/syscalls/sys_read.c \
		src/syscalls/sys_write.c \
		src/syscalls/sys_close.c \
		src/syscalls/sys_execve.c \
		src/syscalls/sys_fork.c \
		src/syscalls/sys_exit.c \
		src/syscalls/sys_getpid.c \
		src/syscalls/sys_lseek.c \
		src/syscalls/sys_chdir.c \
		src/syscalls/sys_sbrk.c \
		src/syscalls/sys_waitpid.c \
		src/syscalls/sys_stat.c \
		src/syscalls/sys_cwd.c \
		src/syscalls/sys_dbgprocs.c \
		src/lib/kmemcpy.c \
		src/lib/kputnbr.c \
		src/lib/kputnbr_base.c \
		src/lib/kputstr.c \
		src/lib/krevstr.c \
		src/lib/kstrcmp.c \
		src/lib/kprintf.c \
		src/lib/ksprintf.c \
		src/lib/kstrdup.c \
		src/lib/add_in_list.c \
		src/lib/rm_from_list.c \
		src/lib/free_list.c \
		src/lib/strchr.c \

ASRCS	=	src/isrs.s \
		src/gdt_flush.s \
		src/read_eip.s \
		src/do_switch.s \
		src/lib/kstrlen.s \
		src/lib/kmemset.s \
		src/switch_registers.s \
		src/switch_page_directory.s \
		src/copy_frame.s \

CC	=	gcc
AS	=	as
LD	=	ld

NAME	=	kernel.bin

INCLUDES=	-Iinclude/
CFLAGS	=	-Wall -W -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin $(INCLUDES)
AFLAGS	=
LDFLAGS	=	--oformat binary -Ttext $(BASE_ADDR)

COBJS	=	$(CSRCS:.c=.o)
AOBJS	=	$(ASRCS:.s=.o)

$(NAME): $(AOBJS) $(COBJS)
	$(LD) $(LDFLAGS) $(COBJS) $(AOBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(COBJS) $(AOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.s.o:
	$(AS) $(AFLAGS) -o $@ $<
