/*
** EPITECH PROJECT, 2019
**  SNAKE GAME
** File description:
** snake.c
*/

#include "my.h"
#include "snake.h"
#include <time.h>

void initialize_ncurses(void)
{
    initscr();
    curs_set(0);
    keypad(stdscr, FALSE);
    notimeout(stdscr, FALSE);
    timeout(0.1);
    noecho();
    refresh();
}

void malloc_my_map(data_t *data)
{
    data->map = NULL;
    data->map = malloc(sizeof(char *) * MAP_HEIGHT);
    for (int i = 0; i < MAP_HEIGHT; i++){
        data->map[i] = NULL;
        data->map[i] = malloc(sizeof(char) * MAP_WIDTH + 1);
        data->map[i][MAP_WIDTH] = '\0';
        for (int j = 0; j < MAP_WIDTH; j++)
            data->map[i][j] = ' ';
    }
}

void fill_my_map(data_t *data)
{
    for (int i = 0; i < MAP_WIDTH; i++){
        data->map[0][i] = '#';
        data->map[MAP_HEIGHT - 1][i] = '#';
    }
    for (int i = 0; i < MAP_HEIGHT; i++){
        data->map[i][0] = '#';
        data->map[i][MAP_WIDTH - 1] = '#';
    }
}

void initialize_data(data_t *data)
{
    data->key = 0;
    data->game_isActive = 1;
    data->begin_time = time(NULL);
    data->timer = 0;
    malloc_my_map(data);
    fill_my_map(data);
}

void initialize_snake(data_t *data)
{
    int i = 0;
    int a = 0;

    data->snake.level = 1;
    data->snake.life = 5;
    data->snake.length = 5;
}

void print_small(void)
{
    clear();
    mvprintw(LINES / 2, COLS / 2 - 5, "SO SMALL !");
    refresh();
}

void print_map(data_t *data)
{
    int level_alignement = MAP_WIDTH / 10;
    int time_alignement = 0;
    int life_alignement = 0;
    printw("\n");
    for (int i = 0; i < level_alignement; i++)
        printw(" ");
    printw("LEVEL : %d", data->snake.level);
    time_alignement = MAP_WIDTH / 2 - my_strlen("LEVEL : ") - my_number_len(data->snake.level) - (my_strlen("TIME : :") + 4) / 2 - level_alignement;
    for (int i = 0; i < time_alignement; i++)
        printw(" ");
    printw("TIME : ");
    if (my_number_len(data->timer / 60) == 1)
        printw("0");
    printw("%d", data->timer / 60);
    printw(":");
    if (my_number_len(data->timer % 60) == 1)
        printw("0");
    printw("%d", data->timer % 60);
    life_alignement = time_alignement;
    for (int i = 0; i < life_alignement; i++)
        printw(" ");
    printw("LIFE : %d\n\n", data->snake.life);
    for (int i = 0; i < MAP_HEIGHT; i++)
        printw("%s\n", data->map[i]);
}

void game_loop(data_t *data)
{
    int time_checker = 0;

    while (data->game_isActive){
        time_checker = time(NULL);
        data->timer = time(NULL) - data->begin_time;
        if (LINES < MAP_HEIGHT || COLS < MAP_WIDTH)
            print_small();
        else {
            clear();
            print_map(data);
            refresh();
            data->key = getch();
        }
        while (time(NULL) < time_checker + 0.1);
    }

}

int main(void)
{
    data_t data;

    initialize_ncurses();
    initialize_data(&data);
    initialize_snake(&data);
    game_loop(&data);
    endwin();
    return (0);
}
