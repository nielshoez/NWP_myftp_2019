/*
** EPITECH PROJECT, 2020
** quit
** File description:
** quit
*/

#include "server.h"
static void client_disconnected(client_t *client)
{
    close(client->fd);
    client->quit = true;
    client->fd = 0;
    client->is_log = false;
}

void quit(client_t *client, int ac, char **av)
{
    server_response(client, CLOSING_CONNECTION);
    client_disconnected(client);
}
