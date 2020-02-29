##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## COMPILE LIBMY.A
##

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

LIB = libmy.a

INCLUDE = my.h

all:	$(LIB)

$(LIB):	$(OBJ)
	ar rc $(LIB) $(OBJ)
	cp $(LIB) ../
	cp $(INCLUDE) ../../include/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(LIB) $(LIB)
	rm -f ../../include/$(INCLUDE)

re: fclean all
