/*
** EPITECH PROJECT, 2019
**  LIB MY
** File description:
** My.h
*/

#ifndef MY_H_
#define MY_H_

#include <stddef.h>
#include <unistd.h>

void my_putchar(char c);
int my_strlen(char const *str);
void my_put_nbr(int nb);
int my_putstr(char const *str);
int my_power(int x, int y);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strcat(char *dest, char const *src);
int my_char_to_int(char *str);
int my_isint(char *str);
int my_atoi(char const *str);
int my_number_len(int nb);
char *my_buffer(char const *filepath, int size);
ssize_t write(int fd, const void *buf, size_t count);

#endif /* MY_H_ */
