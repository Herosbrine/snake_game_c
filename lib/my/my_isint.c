/*
** EPITECH PROJECT, 2019
** int verification
** File description:
** my_isint
*/

#include "my.h"

int my_isint(char *str)
{
    char *str2 = "2147483647";
    int i = 0;

    if (str[0] == '0')
        return (-1);
    if (my_strlen(str) > 10)
        return (-1);
    if (my_strlen(str) < 10)
        return (1);
    for (int i = 0; i < my_strlen(str); i++){
        if (str[i] > str2[i])
            return (-1);
    }
    return (1);
}
