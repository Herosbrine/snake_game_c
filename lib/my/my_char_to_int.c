/*
** EPITECH PROJECT, 2019
** CHAR TO INT
** File description:
** my_char_to_int
*/

#include "my.h"

int my_char_to_int(char *str)
{
    int taille = my_strlen(str);
    int resultat = 0;

    for (int i = 0; i < taille; i++)
        resultat += (str[i] - 48) * my_power(10, taille - 1 - i);
    return (resultat);
}
