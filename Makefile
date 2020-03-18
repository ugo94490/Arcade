##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

SRC	=	Arcade.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	arcade

LDFLAGS		=	-lsfml-window -lsfml-graphics -lsfml-system -lncurses -ldl `sdl-config --libs --cflags` -lSDL_image

CPPFLAGS	=	-I./include

$(NAME):	games graphicals core

all:	$(NAME)

core:	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS)

graphicals:
	make -C lib

games:
	make -C games

clean:
	rm -f $(OBJ)
	make -C lib clean
	make -C games clean

fclean:	clean
	rm -f $(NAME)
	make -C lib fclean
	make -C games fclean

re: fclean all

.PHONY: all clean fclean re games graphicals core
