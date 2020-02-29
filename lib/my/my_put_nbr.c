/*
** EPITECH PROJECT, 2019
** First C Programming
** File description:
** my_put_nbr
*/

#include "my.h"

void my_put_nbr(int nb)
{
    int c = 1;
    int m = 0;

    if (nb == 0)
        my_putchar('0');
    if (nb < 0){
        my_putchar('-');
        nb = nb * (-1);
    }
    for (int i = 1; i < nb; i = i * 10)
        c++;
    for (int j = 1; j <= nb; j = j * 10){
        if (j == nb)
            my_putchar('1');
    }
    while (c > 1){
        m = nb % (my_power(10, c - 1)) / my_power(10, c - 2);
        c--;
        my_putchar(m + 48);
    }
}
