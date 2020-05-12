/*
** EPITECH PROJECT, 2020
** pasv
** File description:
** pasv
*/

#include "server.h"
#include <stdlib.h>
#include <time.h>

int init_passv(client_t *client, struct sockaddr_in *sock_in)
{
    socklen_t size = sizeof(sock_in);
    srand(time(NULL));
    int r_port = random() % 6500 + 1024;

    printf("port == %d\n", r_port);
    sock_in->sin_port = htons(r_port);
    sock_in->sin_family = AF_INET;
    sock_in->sin_addr.s_addr = INADDR_ANY;
    if (bind(client->fd_mod, (const struct sockaddr *)sock_in, \
             sizeof(*sock_in)) == -1) {
        return (1);
    }
    if (listen(client->fd_mod, 1) == -1)
        return (1);
    if (getsockname(client->fd_mod, (struct sockaddr *)sock_in, &size) == -1)
        return (1);
    client->passv_port = ntohs(sock_in->sin_port);
    return (0);
}

int pasv_mod(client_t *client, struct protoent *pr_e)
{
    struct sockaddr_in sock_in;

    if (client->fd_mod != -1)
        close(client->fd_mod);
    pr_e = getprotobyname("TCP");
    if (pr_e == NULL)
        return (1);
    client->fd_mod = socket(AF_INET, SOCK_STREAM, pr_e->p_proto);
    if (client->fd_mod == -1)
        return (1);
    return (init_passv(client, &sock_in));
}

void print_pasv(char **tab, client_t *client)
{
    dprintf(client->fd, "227 Entering Passive Mode (");
    for (int i = 0; tab[i]; i++) {
        dprintf(client->fd, "%s,", tab[i]);
    }
    dprintf(client->fd, "%d,%d).\n", client->passv_port / 256,  \
            client->passv_port % 256);
}

void pasv(client_t *client, int ac, char **av)
{
    struct protoent *pr_e = NULL;
    char *my_ip;
    char **ip;

    if (!client->is_log) {
        server_response(client, NOT_LOGGED_IN);
        return;
    } else
        if (pasv_mod(client, pr_e) == 1) {
            dprintf(client->fd, "500 Illegal PASV\n");
        } else {
            my_ip = strdup(client->ip);
            ip = str_to_tab(my_ip, '.');
            free(my_ip);
            print_pasv(ip, client);
            client->is_pasv = true;
        }
}