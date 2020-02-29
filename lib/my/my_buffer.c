/*
** EPITECH PROJECT, 2019
** OPEN WRITE MALLOC
** File description:
** my_buffer.c
*/

#include "my.h"
#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

char *my_buffer(char const *filepath, int size)
{
    char *buffer = malloc(sizeof(char) * size + 1);
    int fd = 0;
    int resultat = 0;

    buffer[size] = '\0';
    fd = open(filepath, O_RDONLY);
    if (fd == -1){
        endwin();
        exit (84);
    }
    resultat = read(fd, buffer, size);
    if (resultat == 0){
        endwin();
        exit (84);
    }
    close(fd);
    if (buffer[size - 1] == '\0')
        return (buffer);
    size++;
    my_buffer(filepath, size);
}
