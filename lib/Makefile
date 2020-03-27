##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

all:
	make -C libNcurses
	make -C libSFML
	make -C libSDL

$(NAME):
	make -C libNcurses
	make -C libSFML
	make -C libSDL

clean:
	make -C libNcurses clean
	make -C libSFML clean
	make -C libSDL clean

fclean: clean
	make -C libNcurses fclean
	make -C libSFML fclean
	make -C libSDL fclean

re:	fclean all

.PHONY: fclean all clean re tests_run
