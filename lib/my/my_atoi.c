/*
** EPITECH PROJECT, 2019
** ATOI
** File description:
** my_atoi
*/

#include "my.h"

int my_atoi(char const *str)
{
    int taille = my_strlen(str);
    int resultat = 0;

    for (int i = 0; i < taille; i++)
        resultat += (str[i] - 48) * my_power(10, (taille - (i + 1)));
    return (resultat);
}
