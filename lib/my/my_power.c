/*
** EPITECH PROJECT, 2019
** First C Programming
** File description:
** my_power
*/

#include "my.h"

int my_power(int x, int y)
{
    int r = 1; 

    while (y >= 1){
        r *= x;
        y--;
    }
    return (r);
}
