/*
** EPITECH PROJECT, 2020
** pwd
** File description:
** pwd
*/

#include "server.h"

void pwd(client_t *client, int ac, char **av)
{
    char buff[4096];

    if (!client->is_log) {
        server_response(client, NOT_LOGGED_IN);
        return;
    }
    if (!getcwd(buff, sizeof(buff)))
        server_response(client, COMMAND_UNKNOWN);
    else {
        server_response(client, DIRECTORY_OK);
        dprintf(client->fd, "257 \"%s\"\n", buff);
    }
}
