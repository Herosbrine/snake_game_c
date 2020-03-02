/*
** EPITECH PROJECT, 2019
**  SNAKE PROJECT
** File description:
** snake.h
*/

#ifndef SNAKE_H_
#define SNAKE_H_

#include <ncurses.h>
#include <SFML/System.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define TIMEOF(x)   sfTime_asMilliseconds(sfClock_getElapsedTime(x))

#define MAP_WIDTH      170
#define MAP_HEIGHT     40
#define MAX_LENGHT     200
#define LENGHT_SNAKE   120
#define LIFE_SNAKE     5

#define LEFT         1
#define RIGHT        2
#define UP           3
#define DOWN         4

typedef struct cas_s
{
    int is_active;
    int pos_x;
    int pos_y;
    int direction;
}cas_t;

typedef struct snake_s
{
    int level;
    int life;
    int length;
    cas_t *cas;
}snake_t;

typedef struct data_s
{
    int key;
    int game_isActive;
    int begin_time;
    int timer;
    char **map;
    sfClock *clock_move;
    snake_t snake;
}data_t;

#endif /* SNAKE_H_ */
