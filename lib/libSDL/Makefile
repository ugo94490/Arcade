##
## EPITECH PROJECT, 2020
## sokoban
## File description:
## Makefile
##

SRC		=	LibSDL.cpp

NAME	=	../lib_arcade_sdl.so

CC		=	g++

CPPFLAGS = -I./include -I../../include `sdl-config --libs --cflags` -lSDL_image -lSDL_ttf

RM		=	rm -f

$(NAME) 	:
			-$(CC) $(CPPFLAGS) -c -fpic $(SRC)
			-$(CC) $(CPPFLAGS) -shared -o $(NAME) *.o

all		:	$(NAME)

clean 		:
			$(RM) *.gcno *.gcda *.o

fclean 		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY 		:	all clean fclean re tests_run
