##
## Makefile for mk in /home/mk/duc_l_mk
## 
## Made by Mortal Kernel
## Login   <mk@epitech.net>
## 
## Started on  Mon Feb  2 15:46:49 2009 Mortal Kernel
## Last update Thu Mar 12 20:24:33 2009 Duc Lionel
##

Stage1_dir	=	Stage1/
Stage1_bin	=	stage1.bin

Stage2_dir	=	Stage2/
Stage2_bin	=	stage2.bin

Kernel_dir	=	Kernel/
Kernel_bin	=	kernel.bin

NAME		=	bootfloppy.img

all: 
	@make -C $(Stage1_dir)
	@cp $(Stage1_dir)$(Stage1_bin) ./$(Stage1_bin)
	@make -C $(Stage2_dir)
	@cp $(Stage2_dir)$(Stage2_bin) ./$(Stage2_bin)
	@make -C $(Kernel_dir)
	@cp $(Kernel_dir)$(Kernel_bin) ./$(Kernel_bin)
	@cat $(Stage1_bin) $(Stage2_bin) $(Kernel_bin) > $(NAME)
	@echo "Floppy image updated"

clean: 
	rm -f $(Stage1_bin) $(Stage2_bin) $(Kernel_bin)

fclean: clean
	rm -f $(NAME)
	make -C $(Stage1_dir) fclean
	make -C $(Stage2_dir) fclean
	make -C $(Kernel_dir) fclean

$(Stage1_bin):
		make -C $(Stage1_dir)
		cp $(Stage1_dir)$(Stage1_bin) ./$(Stage1_bin)

$(Stage2_bin):
		make -C $(Stage2_dir)
		cp $(Stage2_dir)$(Stage2_bin) ./$(Stage2_bin)

$(Kernel_bin):
		make -C $(Kernel_dir)
		cp $(Kernel_dir)$(Kernel_bin) ./$(Kernel_bin)

re: fclean all
