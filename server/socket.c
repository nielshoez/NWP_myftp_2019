/*
** EPITECH PROJECT, 2020
** sockets
** File description:
** socket
*/

#include "server.h"
#include "errno.h"

void bind_socket(socks_t *socks)
{
    if ((bind(socks->sockfd, (SA*)&socks->servaddr,
            sizeof(socks->servaddr))) != 0) {
        perror("socket bind failed...\n");
        exit(84);
    }
    else
        printf("Socket successfully binded..\n");
}

void listen_client(socks_t *socks)
{
    int len;

    if ((listen(socks->sockfd, 5)) != 0) {
        perror("Listen failed...\n");
        exit(84);
    }
    else
        printf("Server listening..\n");
}

int accept_connexion(socks_t *socks)
{
    int connfd;
    struct sockaddr_in cli;
    int len = sizeof(cli);

    connfd = accept(socks->sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        perror("server acccept failed...\n");
        exit(84);
    }
    else
        printf("server acccept the client...\n");
    return (connfd);
}

socks_t *init_socks(uint64_t port)
{
    socks_t *socks = malloc(sizeof(socks_t));
    int sockfd = 0;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socks == NULL)
        exit(84);
    if (sockfd == -1) {
        exit(84);
    } else
        socks->sockfd = sockfd;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);
    socks->servaddr = servaddr;
    return (socks);
}

int select_socket(socks_t *socks, client_t *client,
                client_t **client_socket)
{
    fd_set rfs;
    int sd = 0;
    int activity = 0;
    int max_sd = 0;

    while (1) {
        FD_ZERO(&rfs);
        FD_SET(socks->sockfd, &rfs);
        for (int i = 0; i < MAXCLIENT; ++i) {
            sd = client_socket[i]->fd;
            if (sd > 0)
                FD_SET(sd, &rfs);
        }
        max_sd = get_max_sd(client_socket, rfs, socks);
        activity = select( max_sd + 1 , &rfs , NULL , NULL , NULL);
        if ((activity < 0) && (errno != EINTR))
            perror("select error");
        client_socket = cli_socks(socks, rfs, client_socket);
        select_com(rfs, client_socket, sd);
    }
}
