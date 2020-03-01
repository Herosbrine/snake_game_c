/*
** EPITECH PROJECT, 2019
**  SNAKE PROJECT
** File description:
** snake.h
*/

#ifndef SNAKE_H_
#define SNAKE_H_

#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAP_WIDTH    170
#define MAP_HEIGHT   40

typedef struct snake_s
{
    int level;
    int life;
    int length;
}snake_t;

typedef struct data_s
{
    char key;
    int game_isActive;
    int begin_time;
    int timer;
    char **map;
    snake_t snake;
}data_t;

#endif /* SNAKE_H_ */
