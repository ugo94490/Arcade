##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

SRC	=	Arcade.cpp						\
		game/Sokoban.cpp				\
		game/SokoObject.cpp				\
		lib/libSFML/LibSFML.cpp			\
		lib/libNcurses/LibNcurses.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	arcade_soko

CPPFLAGS	=	-I./include

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CPPFLAGS) -lsfml-window -lsfml-graphics -lsfml-system -lncurses

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
