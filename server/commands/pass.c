/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "server.h"

void pass(client_t *client, int ac, char **av)
{
    char *pass = (ac > 1) ? av[1] : "";

    if (strcmp(client->last_command, "USER") != 0) {
        server_response(client, BAD_COMMAND_SEQUENCE);
        return;
    }
    if (!client->is_anon) {
        server_response(client, NOT_LOGGED_IN);
        return;
    }
    server_response(client, LOGGED_IN);
    client->is_log = true;
    client->last_command = "PASS";
}
