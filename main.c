/*
** EPITECH PROJECT, 2019
**  SNAKE GAME
** File description:
** snake.c
*/

#include "my.h"
#include "snake.h"

void initialize_ncurses(void)
{
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
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
    for (; i < data->snake.length; i++)
        data->map[MAP_HEIGHT / 2][MAP_WIDTH / 2 - data->snake.length + i] = '*';
    data->map[MAP_HEIGHT / 2][MAP_WIDTH / 2 - data->snake.length + i] = '>';
}

void print_small(void)
{
    clear();
    mvprintw(LINES / 2, COLS / 2 - 5, "SO SMALL !");
    refresh();
}

void print_map(data_t *data)
{
    printw("\n");
    for (int i = 0; i < MAP_WIDTH / 10; i++)
        printw(" ");
    printw("LEVEL : %d", data->snake.level);
    for (int i = 0; i < MAP_WIDTH - MAP_WIDTH / 10 - 7 - my_number_len(data->snake.life) - MAP_WIDTH / 10 - 8 - my_number_len(data->snake.level); i++)
        printw(" ");
    printw("LIFE : %d\n\n", data->snake.life);
    for (int i = 0; i < MAP_HEIGHT; i++)
        printw("%s\n", data->map[i]);
}

int move_snake(data_t *data)
{
    int y = 0;

    if (data->key == (char)KEY_RIGHT) {
        for (; data->map[MAP_HEIGHT / 2][MAP_WIDTH / 2 - data->snake.length + y] != '*'; y++);
        data->map[MAP_HEIGHT / 2][MAP_WIDTH / 2 - data->snake.length + y] = ' ';
        for (; data->map[MAP_HEIGHT / 2][MAP_WIDTH / 2 - data->snake.length + y] != '>'; y++);
        data->map[MAP_HEIGHT / 2][MAP_WIDTH / 2 - data->snake.length + y] = '*';
        data->map[MAP_HEIGHT / 2][MAP_WIDTH / 2 - data->snake.length + y+1] = '>';
    }
    sleep(0.1);
    return (0);
}

void game_loop(data_t *data)
{
    while (data->game_isActive){
        if (LINES < MAP_HEIGHT || COLS < MAP_WIDTH)
            print_small();
        else {
            clear();
            print_map(data);
            data->key = getch();
            move_snake(data);
            refresh();
        }
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
