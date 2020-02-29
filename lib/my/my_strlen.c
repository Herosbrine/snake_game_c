/*
** EPITECH PROJECT, 2019
** Pointers
** File description:
** my_strlen
*/

#include "my.h"

int my_strlen(char const *str)
{
    int compteur = 0;

    while (*str != '\0'){
        str++;
        compteur++;
    }
    return (compteur);
}
