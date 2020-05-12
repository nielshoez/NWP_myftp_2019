/*
** EPITECH PROJECT, 2020
** select
** File description:
** select
*/

#include "server.h"
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int get_max_sd(client_t **client_socket, fd_set rfs, socks_t *socks)
{
    int max_sd = socks->sockfd;
    int sd = 0;

    for (int i = 0; i < MAXCLIENT; ++i) {
        sd = client_socket[i]->fd;
        if (sd > 0)
            FD_SET(sd, &rfs);
        if (sd > max_sd)
            max_sd = sd;
    }
    return (max_sd);
}

client_t **cli_socks(socks_t *socks, fd_set rfs, client_t **client_socket)
{
    int new_socket = 0;
    struct sockaddr_in cli;
    int len = sizeof(cli);

    if (FD_ISSET(socks->sockfd, &rfs)) {
        if ((new_socket = accept(socks->sockfd, (struct sockaddr *)&cli,
                                (socklen_t *)&len))<0)
            perror("accept");
        for (int i = 0; i < MAXCLIENT; i++) {
            if (client_socket[i]->fd == 0) {
                client_socket[i]->fd = new_socket;
                getsockname(new_socket, (struct sockaddr *)&cli,
                            (socklen_t *)&len);
                client_socket[i]->ip = inet_ntoa(cli.sin_addr);
                server_response(client_socket[i], SERVICE_READY);
                break;
            }
        }
    }
    return (client_socket);
}

void select_com(fd_set rfs, client_t **client_socket, int sd)
{
    for (int i = 0; i < MAXCLIENT; i++) {
        sd = client_socket[i]->fd;
        if (FD_ISSET( sd , &rfs))
            communication(client_socket[i]);
    }
}
