/*
** EPITECH PROJECT, 2020
** list
** File description:
** list
*/

#include "server.h"
#include "string.h"

static char *make_command(size_t argc, char **argv)
{
    char *cmd = NULL;
    size_t length = strlen("ls -l");

    for (size_t i = 1; i < argc; ++i)
        length += strlen(argv[i]) + 1;
    cmd = calloc(length + 1, sizeof(char));
    if (!cmd)
        return (NULL);
    strcpy(cmd, "ls -l");
    for (size_t i = 1; i < argc; ++i) {
        strcat(cmd, " ");
        strcat(cmd, argv[i]);
    }
    return (cmd);
}

static int disp_list(char **av, int fd_new, client_t *client, int ac)
{
    FILE *pp;
    char str[4096];

    if (ac == 1)
        pp = popen("ls -l", "r");
    else if (ac > 1)
        pp = popen(make_command(ac, av), "r");
    if (!pp) {
        close(fd_new);
        fclose(pp);
        return (1);
    } else {
        server_response(client, OPENING_DATA_CONNECTION);
        while (fgets(str, 4096, pp))
            dprintf(fd_new, "%s", str);
        fclose(pp);
        server_response(client, CLOSING_DATA_CONNECTION);
        client->is_pasv = false;
        close(fd_new);
    }
}

static void accept_list(char **av, client_t *client, int ac)
{
    struct sockaddr_in s_in;
    socklen_t size = sizeof(s_in);
    int fd_new = accept(client->fd_mod, (struct sockaddr *)&s_in, &size);

    if (fd_new == -1)
        server_response(client, NEED_PASV_OR_PORT);
    else {
        if (disp_list(av, fd_new, client, ac) == 1)
            server_response(client, FILE_UNAVAILABLE);
    }
}

void list(client_t *client, int ac, char **av)
{
    if (!client->is_log) {
        server_response(client, NOT_LOGGED_IN);
        return;
    }
    if (!client->is_pasv) {
        server_response(client, NEED_PASV_OR_PORT);
        return;
    } else
        accept_list(av, client, ac);
}
