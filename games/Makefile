##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

all:
	make -C sokoban
	make -C Pacman

$(NAME):
	make -C sokoban
	make -C Pacman

clean:
	make -C sokoban clean
	make -C Pacman clean

fclean: clean
	make -C sokoban fclean
	make -C Pacman fclean

re:	fclean all

.PHONY: fclean all clean re tests_run
