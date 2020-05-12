/*
** EPITECH PROJECT, 2020
** dele
** File description:
** dele
*/

#include "server.h"
#include <sys/stat.h>

void dele(client_t *client, int ac, char **av)
{
    struct stat buf;

    if (!client->is_log) {
        server_response(client, NOT_LOGGED_IN);
        return;
    }
    if (ac < 2) {
        server_response(client, PARAMETERS_UNKNOWN);
        return;
    }
    if (stat(av[1], &buf) == -1 || !S_ISREG(buf.st_mode)) {
        server_response(client, FILE_UNAVAILABLE);
        return;
    }
    if (unlink(av[1]) == -1) {
        server_response(client, FILE_UNAVAILABLE);
        return;
    }
    server_response(client, FILE_ACTION_OK);
}
