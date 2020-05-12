/*
** EPITECH PROJECT, 2020
** stor
** File description:
** stor
*/

#include "server.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int write_file(char **av, int fd, client_t *client)
{
    int file = open(av[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    char str[2048];
    int i;

    if (file == -1)
            return (1);
    server_response(client, OPENING_DATA_CONNECTION);
    while (1) {
        i = read(fd, str, 2047);
        if (i <= 0)
            break;
        str[i] = '\0';
        dprintf(file, "%s", str);
    }
    server_response(client, CLOSING_DATA_CONNECTION);
    close(client->fd_mod);
    client->is_pasv = false;
    close(file);
    return (0);
}

static void accept_stor(char **av, client_t *client)
{
    struct sockaddr_in s_in;
    socklen_t size = sizeof(s_in);
    int fd_new = accept(client->fd_mod, (struct sockaddr *)&s_in, &size);

    if (fd_new == -1)
        server_response(client, NEED_PASV_OR_PORT);
    else {
        if (write_file(av, fd_new, client) == 1)
            server_response(client, FILE_UNAVAILABLE);
    }
}

void stor(client_t *client, int ac, char **av)
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
        accept_stor(av, client);
}
