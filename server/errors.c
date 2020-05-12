/*
** EPITECH PROJECT, 2020
** errors.c
** File description:
** errors
*/

#include "server.h"
#define HELP "wrong arguments.\n./server port ip"

int check_args(int ac, char **av)
{
    if (ac != 3) {
        printf("%s\n", HELP);
        return (-1);
    }
    return (atoi(av[1]));
}