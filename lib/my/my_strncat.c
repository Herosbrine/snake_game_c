/*
** EPITECH PROJECT, 2019
** LIB
** File description:
** my_strncat
*/

#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int i = 0;
    int j = my_strlen(dest);
    int taille = my_strlen(src) + my_strlen(dest);

    dest[taille];
    dest[taille] = '\0';
    while (src[i] != '\0' && j < taille && i < nb){
        dest[j] = src[i];
        i++;
        j++;
    }
    return (dest);
}
