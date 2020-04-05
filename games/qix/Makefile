##
## EPITECH PROJECT, 2020
## qix
## File description:
## Makefile
##

SRC		=	Qix.cpp			\
			QixGround.cpp	\
			QixPlayer.cpp	\
			QixTrail.cpp	\
			QixQix.cpp		\
			QixQixNode.cpp	\
			QixSpark.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	../lib_arcade_qix.so

CC		=	g++

CPPFLAGS = -I./include -I../../include -Wall -Wextra

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

.PHONY 		:	all clean fclean re