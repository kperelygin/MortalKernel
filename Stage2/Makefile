##
## Makefile for mk in /home/mk/duc_l_mk/Stage1
## 
## Made by Mortal Kernel
## Login   <mk@epitech.net>
## 
## Started on  Mon Feb  2 15:51:35 2009 Mortal Kernel
## Last update Fri Feb 20 06:26:28 2009 Duc Lionel
##

SRC	=	stage2.s \

OBJ	=	$(SRC:.s=.o)
NAME	=	stage2.bin
AFLAGS	=	-f bin
AS	=	nasm


$(NAME): $(OBJ)
	cp $(OBJ) $(NAME)

all:	$(NAME)

clean:
	rm -f $(OBJ)
	rm -f *~

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.s.o:
	$(AS) $(AFLAGS) $< -o $@

.PHONY: all clean fclean re
