##
## EPITECH PROJECT, 2020
## sokoban
## File description:
## Makefile
##

SRC		=	LibSDL.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	../lib_arcade_sdl.so

CC		=	g++

CPPFLAGS = -I./include -I../../include `sdl-config --libs --cflags` -lSDL_image 

RM		=	rm -f

$(NAME) 	: 	$(OBJ)
			-$(CC) $(CPPFLAGS) -c -fpic $(SRC)
			-$(CC) $(CPPFLAGS) -shared -o $(NAME) $(OBJ)

all		:	$(NAME)

clean 		:
			$(RM) $(OBJ) $(OBJ_T) *.gcno *.gcda

fclean 		:	clean
			$(RM) $(NAME) $(NAME_T)

re		:	fclean all

.PHONY 		:	all clean fclean re tests_run
