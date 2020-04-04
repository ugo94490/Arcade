##
## EPITECH PROJECT, 2020
## Menu
## File description:
## Makefile
##

SRC		=	Menu.cpp		\
			MenuObject.cpp	\

SRC_T		=

OBJ		=	$(SRC:.cpp=.o)

OBJ_T	=	$(SRC_T:.cpp=.o)

NAME	=	../lib_arcade_menu.so

NAME_T	=	unit_tests

CC		=	g++

CPPFLAGS = -I./include -I../../include -Wall -Wextra

TESTS_FLAGS	= -I./include -I../../include --coverage -lcriterion

RM		=	rm -f

$(NAME) 	: 	$(OBJ)
			$(CC) $(CPPFLAGS) -c -fpic $(SRC)
			$(CC) $(CPPFLAGS) -shared -o $(NAME) $(OBJ)

all		:	$(NAME)

tests_run:
	g++ -o $(NAME_T) $(SRC_T) $(TESTS_FLAGS) tests/test_A*.cpp
	./unit_tests
	@echo "GCC_unit_tests: [OK]"


clean 		:
			$(RM) $(OBJ) $(OBJ_T) *.gcno *.gcda

fclean 		:	clean
			$(RM) $(NAME) $(NAME_T)

re		:	fclean all

.PHONY 		:	all clean fclean re tests_run
