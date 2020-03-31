##
## EPITECH PROJECT, 2020
## sokoban
## File description:
## Makefile
##

SRC		=	Nibbler.cpp		\
			NibObject.cpp

SRC_T		=

OBJ		=	$(SRC:.cpp=.o)

OBJ_T	=	$(SRC_T:.cpp=.o)

NAME	=	../game_nibbler.so

NAME_T	=	unit_tests

CC		=	g++

CPPFLAGS = -I./include -I../../include -Wall -Wextra -g3

TESTS_FLAGS	=	--coverage -lcriterion

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
