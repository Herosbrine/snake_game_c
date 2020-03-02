##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## SNAKE GAME
##

SRC = main.c \

FLAGS =-I./include

LIB =-lmy -L./lib/my

NAME = snake

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C ./lib/my/
	gcc $(FLAGS) -o $(NAME) $(SRC) $(LIB) -lncurses -lcsfml-system

debug:
	gcc $(FLAGS) -g3 $(SRC) $(LIB)

clean:
	make clean -C ./lib/my/
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./lib/my/
	rm -f $(NAME)

re: fclean all
