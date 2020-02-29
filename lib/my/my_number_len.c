/*
** EPITECH PROJECT, 2019
** lib
** File description:
** my_number_len
*/

#include "my.h"

int my_number_len(int nb)
{
    int res = 0;

    while (nb != 0){
        nb /= 10;
        res++;
    }
    return (res);
}
