##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

all:
	make -C sokoban
	make -C nibbler
	make -C pacman

$(NAME):
	make -C sokoban
	make -C nibbler
	make -C pacman

clean:
	make -C sokoban clean
	make -C nibbler clean
	make -C pacman  clean

fclean: clean
	make -C sokoban fclean
	make -C nibbler fclean
	make -C pacman  fclean

re:	fclean all

.PHONY: fclean all clean re tests_run
