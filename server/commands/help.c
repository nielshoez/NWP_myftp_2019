/*
** EPITECH PROJECT, 2020
** help
** File description:
** help
*/

#include "server.h"

static void all_commands(client_t *client)
{
    server_response(client, HELP_MESSAGE);
    dprintf(client->fd, "USER PASS LIST CWD CDUP QUIT NOOP PWD ");
    dprintf(client->fd, "DELE HELP PASV PORT RETR STOR\n");
}

static void one_command(client_t *client, char *cmd)
{
    if (get_help(cmd) == NULL)
        server_response(client, COMMAND_UNKNOWN);
    else {
        server_response(client, HELP_MESSAGE);
        dprintf(client->fd, "%s\n", get_help(cmd));
    }
}

void help(client_t *client, int ac, char **av)
{
    if (!client->is_log) {
        server_response(client, NOT_LOGGED_IN);
        return;
    }
    if (ac > 1)
        one_command(client, remove_n(av[1]));
    else
        all_commands(client);
}
