/*
** EPITECH PROJECT, 2020
** noop
** File description:
** noop
*/

#include "server.h"

void noop(client_t *client, int ac, char **av)
{
    if (!client->is_log) {
        server_response(client, NOT_LOGGED_IN);
        return;
    } else 
        server_response(client, OK);
}
