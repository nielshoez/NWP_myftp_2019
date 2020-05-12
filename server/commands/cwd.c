/*
** EPITECH PROJECT, 2020
** cwd
** File description:
** cwd
*/

#include "server.h"

void cwd(client_t *client, int ac, char **av)
{
    if (!client->is_log) {
        server_response(client, NOT_LOGGED_IN);
        return;
    }
    if (ac < 2) {
        server_response(client, PARAMETERS_UNKNOWN);
        return;
    }
    if (chdir(av[1]) == 0) {
        server_response(client, FILE_ACTION_OK);
    } else
        server_response(client, FILE_UNAVAILABLE);
}
