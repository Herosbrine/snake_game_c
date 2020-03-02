/*
** EPITECH PROJECT, 2019
**  SNAKE GAME
** File description:
** snake.c
*/

#include "my.h"
#include "snake.h"
#include <time.h>

int random_number(int nb_one, int nb_two)
{
    int a = 0;

    a = rand() % (nb_two - nb_one) + 1 + nb_one;
    return (a);
}

void generate_object(data_t *data)
{
    for (int i = 0; i < MAX_OBJECT; i++){
        if (data->object[i].type == 0){
            data->object[i].type = FOOD;
            data->object[i].pos_x = random_number(1, MAP_HEIGHT - 2);
            data->object[i].pos_y = random_number(1, MAP_WIDTH - 2);
            break;
        }
    }
}

void initialize_object(data_t *data)
{
    data->object = malloc(sizeof(object_t) * MAX_OBJECT);
    for (int i = 0; i < MAX_OBJECT; i++){
        data->object[i].pos_x = 0;
        data->object[i].pos_y = 0;
        data->object[i].type = 0;
    }
}

void initialize_ncurses(void)
{
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    notimeout(stdscr, FALSE);
    timeout(0.01);
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
    data->clock_move = sfClock_create();
    data->begin_time = time(NULL);
    data->timer = 0;
    malloc_my_map(data);
    fill_my_map(data);
}

void reset_game(data_t *data)
{
    data->key = 0;
    data->game_isActive = 1;
    sfClock_restart(data->clock_move);
    data->begin_time = time(NULL);
    data->timer = 0;
    data->snake.score = 0;
    data->snake.life = LIFE_SNAKE;
    data->snake.length = LENGHT_SNAKE;
    data->snake.cas = malloc(sizeof(cas_t) * MAX_LENGHT);
    for (int i = 0; i < MAX_LENGHT; i++){
        data->snake.cas[i].pos_x = 0;
        data->snake.cas[i].pos_y = 0;
        data->snake.cas[i].direction = 0;
    }
    for (int i = 0; i < data->snake.length; i++){
        data->snake.cas[i].direction = RIGHT;
        data->snake.cas[i].pos_x = MAP_HEIGHT / 2;
        data->snake.cas[i].pos_y = MAP_WIDTH / 2 - data->snake.length / 2 + i;
    }
    for (int i = 0; i < data->snake.length; i++){
        data->map[data->snake.cas[i].pos_x][data->snake.cas[i].pos_y] = '-';
    }
}

void initialize_snake(data_t *data)
{
    data->snake.score = 0;
    data->snake.life = LIFE_SNAKE;
    data->snake.length = LENGHT_SNAKE;
    data->snake.cas = malloc(sizeof(cas_t) * MAX_LENGHT);
    for (int i = 0; i < MAX_LENGHT; i++){
        data->snake.cas[i].pos_x = 0;
        data->snake.cas[i].pos_y = 0;
        data->snake.cas[i].direction = 0;
    }
    for (int i = 0; i < data->snake.length; i++){
        data->snake.cas[i].direction = RIGHT;
        data->snake.cas[i].pos_x = MAP_HEIGHT / 2;
        data->snake.cas[i].pos_y = MAP_WIDTH / 2 - data->snake.length / 2 + i;
    }
}

void print_game_over_screen(data_t *data)
{
    mvprintw(LINES / 2 - 3, COLS / 2 - my_strlen("GAME OVER !") / 2, "GAME OVER !");
    mvprintw(LINES / 2 - 1, COLS / 2 - (my_strlen("SCORE : ") + my_number_len(data->snake.score)) / 2, "SCORE : %d", data->snake.score);
    mvprintw(LINES / 2 + 1, COLS / 2 - (my_strlen("HIGH SCORE : ") + my_number_len(data->snake.score)) / 2, "HIGH SCORE : %d", data->snake.score);
    mvprintw(LINES / 2 + 3, COLS / 2 - my_strlen("TO PLAY AGAIN USE SPACE KEY") / 2, "TO PLAY AGAIN USE SPACE KEY");

}

void print_small(void)
{
    clear();
    mvprintw(LINES / 2, COLS / 2 - 5, "SO SMALL !");
    refresh();
}

void print_map(data_t *data)
{
    int score_alignement = MAP_WIDTH / 10;
    int time_alignement = 0;
    int life_alignement = 0;
    printw("\n");
    for (int i = 0; i < score_alignement; i++)
        printw(" ");
    printw("SCORE : %d", data->snake.score);
    time_alignement = MAP_WIDTH / 2 - my_strlen("SCORE : ") - my_number_len(data->snake.score) - (my_strlen("TIME : :") + 4) / 2 - score_alignement;
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
    for (int i = 1; i < MAP_HEIGHT - 1; i++){
        for (int j = 1; j < MAP_WIDTH - 1; j++)
            data->map[i][j] = ' ';
    }
    for (int i = 0; i < data->snake.length; i++){
        data->map[data->snake.cas[i].pos_x][data->snake.cas[i].pos_y] = 'o';
    }
    for (int i = 0; i < MAX_OBJECT; i++) {
        if (data->object[i].type == FOOD) {
            data->map[data->object[i].pos_x][data->object[i].pos_y] = 'G';
            break;
        }
    }
    if (data->snake.cas[data->snake.length - 1].direction == RIGHT)
        data->map[data->snake.cas[data->snake.length - 1].pos_x][data->snake.cas[data->snake.length - 1].pos_y] = '+';
    if (data->snake.cas[data->snake.length - 1].direction == LEFT)
        data->map[data->snake.cas[data->snake.length - 1].pos_x][data->snake.cas[data->snake.length - 1].pos_y] = '+';
    if (data->snake.cas[data->snake.length - 1].direction == UP)
        data->map[data->snake.cas[data->snake.length - 1].pos_x][data->snake.cas[data->snake.length - 1].pos_y] = '+';
    if (data->snake.cas[data->snake.length - 1].direction == DOWN)
        data->map[data->snake.cas[data->snake.length - 1].pos_x][data->snake.cas[data->snake.length - 1].pos_y] = '+';
    for (int i = 0; i < MAP_HEIGHT; i++)
        printw("%s\n", data->map[i]);
}

void actualize_move_key(data_t *data)
{
    int key = getch();

    if (key == 32){
        reset_game(data);
    }
    if (data->key != LEFT && data->key != RIGHT && key == KEY_LEFT){
        data->key = LEFT;
        data->snake.cas[data->snake.length - 1].direction = LEFT;
    }
    if (data->key != RIGHT && data->key != LEFT && key == KEY_RIGHT){
        data->key = RIGHT;
        data->snake.cas[data->snake.length - 1].direction = RIGHT;
    }
    if (data->key != UP && data->key != DOWN && key == KEY_UP){
        data->key = UP;
        data->snake.cas[data->snake.length - 1].direction = UP;
    }
    if (data->key != DOWN && data->key != UP && key == KEY_DOWN){
        data->key = DOWN;
        data->snake.cas[data->snake.length - 1].direction = DOWN;
    }
}

void reset_snake(data_t *data)
{
    data->snake.life -= 1;
    data->snake.length = LENGHT_SNAKE;
    data->key = RIGHT;

    for (int i = 0; i < MAX_LENGHT; i++){
        data->snake.cas[i].pos_x = 0;
        data->snake.cas[i].pos_y = 0;
        data->snake.cas[i].direction = 0;
    }
    for (int i = 0; i < data->snake.length; i++){
        data->snake.cas[i].direction = RIGHT;
        data->snake.cas[i].pos_x = MAP_HEIGHT / 2;
        data->snake.cas[i].pos_y = MAP_WIDTH / 2 - data->snake.length / 2 + i;
    }
    for (int i = 0; i < data->snake.length; i++){
        data->map[data->snake.cas[i].pos_x][data->snake.cas[i].pos_y] = '-';
    }
}

void delete_food(data_t *data, int j)
{
    data->object[j].type = 0;
    data->snake.score += 1000;
    data->snake.length++;
    data->snake.cas[data->snake.length - 1].direction = data->snake.cas[data->snake.length - 2].direction;
    if (data->snake.cas[data->snake.length - 2].direction == LEFT) {
        data->snake.cas[data->snake.length - 1].pos_x = data->snake.cas[data->snake.length - 2].pos_x;
        data->snake.cas[data->snake.length - 1].pos_y = data->snake.cas[data->snake.length - 2].pos_y - 1;
    }
    if (data->snake.cas[data->snake.length - 2].direction == RIGHT) {
        data->snake.cas[data->snake.length - 1].pos_x = data->snake.cas[data->snake.length - 2].pos_x;
        data->snake.cas[data->snake.length - 1].pos_y = data->snake.cas[data->snake.length - 2].pos_y + 1;
    }
    if (data->snake.cas[data->snake.length - 2].direction == UP) {
        data->snake.cas[data->snake.length - 1].pos_x = data->snake.cas[data->snake.length - 2].pos_x - 1;
        data->snake.cas[data->snake.length - 1].pos_y = data->snake.cas[data->snake.length - 2].pos_y;
    }
    if (data->snake.cas[data->snake.length - 2].direction == DOWN) {
        data->snake.cas[data->snake.length - 1].pos_x = data->snake.cas[data->snake.length - 2].pos_x + 1;
        data->snake.cas[data->snake.length - 1].pos_y = data->snake.cas[data->snake.length - 2].pos_y;
    }
}

void snake_move(data_t *data)
{
    if (TIMEOF(data->clock_move) > 90){
        for (int i = 0; i < data->snake.length; i++){
            if (data->snake.cas[i].direction == RIGHT){
                if (i == data->snake.length - 1){
                    if (data->map[data->snake.cas[i].pos_x][data->snake.cas[i].pos_y + 1] != ' ' && data->map[data->snake.cas[i].pos_x][data->snake.cas[i].pos_y + 1] != 'G'){
                        reset_snake(data);
                        return;
                    }
                    if (data->map[data->snake.cas[i].pos_x][data->snake.cas[i].pos_y + 1] == 'G') {
                        for (int j = 0; j < MAX_OBJECT; j++){
                            if (data->object[j].type == FOOD && data->object[j].pos_x == data->snake.cas[i].pos_x && data->snake.cas[i].pos_y + 1 == data->object[j].pos_y){
                                delete_food(data, j);
                                break;
                            }
                        }
                    }
                }
                data->snake.cas[i].pos_y += 1;
            }
            if (data->snake.cas[i].direction == LEFT){
                if (i == data->snake.length - 1){
                    if (data->map[data->snake.cas[i].pos_x][data->snake.cas[i].pos_y - 1] != ' ' && data->map[data->snake.cas[i].pos_x][data->snake.cas[i].pos_y - 1] != 'G'){
                        reset_snake(data);
                        return;
                    }
                    if (data->map[data->snake.cas[i].pos_x][data->snake.cas[i].pos_y - 1] == 'G') {
                        for (int j = 0; j < MAX_OBJECT; j++){
                            if (data->object[j].type == FOOD && data->object[j].pos_x == data->snake.cas[i].pos_x && data->snake.cas[i].pos_y - 1 == data->object[j].pos_y){
                                delete_food(data, j);
                                break;
                            }
                        }
                    }
                }
                data->snake.cas[i].pos_y -= 1;
            }
            if (data->snake.cas[i].direction == UP){
                if (i == data->snake.length - 1){
                    if (data->map[data->snake.cas[i].pos_x - 1][data->snake.cas[i].pos_y] != ' ' && data->map[data->snake.cas[i].pos_x - 1][data->snake.cas[i].pos_y] != 'G'){
                        reset_snake(data);
                        return;
                    }
                    if (data->map[data->snake.cas[i].pos_x - 1][data->snake.cas[i].pos_y] == 'G') {
                        for (int j = 0; j < MAX_OBJECT; j++){
                            if (data->object[j].type == FOOD && data->object[j].pos_x == data->snake.cas[i].pos_x - 1 && data->snake.cas[i].pos_y == data->object[j].pos_y){
                                delete_food(data, j);
                                break;
                            }
                        }
                    }
                }
                data->snake.cas[i].pos_x -= 1;
            }
            if (data->snake.cas[i].direction == DOWN){
                if (i == data->snake.length - 1){
                    if (data->map[data->snake.cas[i].pos_x + 1][data->snake.cas[i].pos_y] != ' ' && data->map[data->snake.cas[i].pos_x + 1][data->snake.cas[i].pos_y] != 'G'){
                        reset_snake(data);
                        return;
                    }
                    if (data->map[data->snake.cas[i].pos_x + 1][data->snake.cas[i].pos_y] == 'G') {
                        for (int j = 0; j < MAX_OBJECT; j++){
                            if (data->object[j].type == FOOD && data->object[j].pos_x == data->snake.cas[i].pos_x + 1 && data->snake.cas[i].pos_y == data->object[j].pos_y){
                                delete_food(data, j);
                                break;
                            }
                        }
                    }
                }
                data->snake.cas[i].pos_x += 1;
            }
        }
        for (int i = 0; i < data->snake.length - 1; i++)
            data->snake.cas[i].direction = data->snake.cas[i + 1].direction;
        sfClock_restart(data->clock_move);
    }
}

int there_are_not_food(data_t *data)
{
    for (int i = 0; i < MAX_OBJECT; i++) {
        if (data->object[i].type == FOOD)
            return (0);
    }
    return (1);
}
void game_loop(data_t *data)
{
    while (data->game_isActive){
        data->timer = time(NULL) - data->begin_time;
        if ((LINES < MAP_HEIGHT || COLS < MAP_WIDTH) && data->snake.life > 0)
            print_small();
        else if (data->snake.life > 0) {
            clear();
            actualize_move_key(data);
            snake_move(data);
            data->snake.score += 1;
            if (there_are_not_food(data)){
                generate_object(data);
            }
            print_map(data);
            refresh();
        }
        else {
            clear();
            if (getch() == 32){
                reset_game(data);
                continue;
            }
            print_game_over_screen(data);
            refresh();
        }
        usleep(80000);
    }
}

int main(void)
{
    data_t data;

    srand(time(NULL));
    initialize_ncurses();
    initialize_data(&data);
    initialize_snake(&data);
    initialize_object(&data);
    game_loop(&data);
    endwin();
    return (0);
}
