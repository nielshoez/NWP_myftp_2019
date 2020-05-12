/*
** EPITECH PROJECT, 2020
** cdup
** File description:
** cdup
*/

#include "server.h"

void cdup(client_t *client, int ac, char **av)
{
    if (!client->is_log) {
        server_response(client, NOT_LOGGED_IN);
        return;
    }
    if (chdir("../") == 0) {
        server_response(client, OK);
    } else
        server_response(client, FILE_UNAVAILABLE);
}
