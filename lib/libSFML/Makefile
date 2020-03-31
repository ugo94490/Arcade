##
## EPITECH PROJECT, 2020
## sokoban
## File description:
## Makefile
##

SRC		=	LibSFML.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	../lib_arcade_sfml.so

CC		=	g++

CPPFLAGS = -I./include -I../../include -lsfml-window -lsfml-graphics -lsfml-system

RM		=	rm -f

$(NAME) 	: 	$(OBJ)
			$(CC) $(CPPFLAGS) -c -fpic $(SRC)
			$(CC) $(CPPFLAGS) -shared -o $(NAME) $(OBJ)

all		:	$(NAME)

clean 		:
			$(RM) $(OBJ) $(OBJ_T) *.gcno *.gcda

fclean 		:	clean
			$(RM) $(NAME) $(NAME_T)

re		:	fclean all

.PHONY 		:	all clean fclean re tests_run
