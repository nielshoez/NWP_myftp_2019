/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
    int sockfd = 0;
    int port = check_args(ac, av);
    struct sockaddr_in servaddr;
    socks_t *socks;
    client_t *client;
    client_t **client_socket;

    if (port == -1)
        exit (84);
    socks = init_socks(port);
    client = init_client(av[2], socks->ip);
    client_socket = tab_client(av[2], socks->ip);
    bind_socket(socks);
    listen_client(socks);
    select_socket(socks, client, client_socket);
    close(socks->sockfd);
}