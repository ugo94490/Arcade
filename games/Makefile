##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

all:
	make -C sokoban
	make -C nibbler

$(NAME):
	make -C sokoban
	make -C nibbler

clean:
	make -C sokoban clean
	make -C nibbler clean

fclean: clean
	make -C sokoban fclean
	make -C nibbler fclean

re:	fclean all

.PHONY: fclean all clean re tests_run
