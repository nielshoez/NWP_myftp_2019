/*
** EPITECH PROJECT, 2020
** retr
** File description:
** retr
*/

#include "server.h"

static int disp_file(char **av, int fd_new, client_t *client)
{
    FILE *file = fopen(av[1], "r+");
    char str[4096];

    if (file == NULL) {
        close(fd_new);
        fclose(file);
        return (1);
    }
    else {
        server_response(client, OPENING_DATA_CONNECTION);
        while (fgets(str, 4096, file))
            dprintf(fd_new, "%s", str);
        fclose(file);
        server_response(client, CLOSING_DATA_CONNECTION);
        client->is_pasv = false;
        close(fd_new);
        return (0);
    }
}

static void accept_retrieve(char **av, client_t *client)
{
    struct sockaddr_in s_in;
    socklen_t size = sizeof(s_in);
    int fd_new = accept(client->fd_mod, (struct sockaddr *)&s_in, &size);

    if (fd_new == -1)
        server_response(client, NEED_PASV_OR_PORT);
    else {
        if (disp_file(av, fd_new, client) == 1)
            server_response(client, FILE_UNAVAILABLE);
    }
}

void retr(client_t *client, int ac, char **av)
{
    if (ac != 2) {
        server_response(client, PARAMETERS_UNKNOWN);
        return;
    }
    if (!client->is_log) {
        server_response(client, NOT_LOGGED_IN);
        return;
    }
    if (!client->is_pasv) {
        server_response(client, NEED_PASV_OR_PORT);
        return;
    } else
        accept_retrieve(av, client);
}
