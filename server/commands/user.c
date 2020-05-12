/*
** EPITECH PROJECT, 2020
** user
** File description:
** user
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

void user(client_t *client, int ac, char **av)
{
    if (ac != 2)
        server_response(client, PARAMETERS_UNKNOWN);
    if (strcasecmp(av[1], "anonymous") == 0)
        client->is_anon = true;
    else {
        client->username = calloc(1, sizeof(char) * strlen(av[1]));
        if (client->username == NULL)
            return;
        strcpy(client->username, av[1]);
    }
    client->last_command = "USER";
    server_response(client, NEED_PASSWORD);
}
