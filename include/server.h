/*
** EPITECH PROJECT, 2020
** server
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdbool.h>
#include "protocol.h"
#define MAX 80
#define MAXCLIENT 42
#define SA struct sockaddr
#define SLEN(a) (sizeof(a) / sizeof(*a))

typedef struct socks_s {
    struct sockaddr_in servaddr;
    int sockfd;
    char *ip;
} socks_t;

typedef struct client_s {
    int fd;
    int fd_mod;
    int passv_port;
    char *username;
    char *password;
    char *ip;
    char *last_command;
    char *path;
    bool quit;
    bool is_anon;
    bool is_log;
    bool is_pasv;
} client_t;

typedef struct map {
    char *key;
    void (*func)(client_t *, int, char **);
} map;

typedef void (*fptr)(client_t *, int, char **);


void communication(client_t *client);
int select_socket(socks_t *socks, client_t *client,
                    client_t **client_socket);
client_t *init_client(char *path, char *ip);
void bind_socket(socks_t *socks);
void listen_client(socks_t *socks);
int accept_connexion(socks_t *socks);
socks_t *init_socks(uint64_t port);
int check_args(int ac, char **av);
void select_loop(socks_t *socks, client_t *client,
                fd_set active_fd_set, fd_set read_fd_set);
char **str_to_tab(char *line, char delim);
char *my_strclean(char *line);
fptr get_args(char *arg);
int server_response(client_t *client, code_t code);
int get_count(char *line, char delim);
char *get_message(code_t code);
char *remove_n(char *str);
char *get_help(char *command);
char *get_next_line(int fd);
void handle_commands(client_t *client);
client_t **tab_client(char *path, char *ip);

int get_max_sd(client_t **client_socket, fd_set rfs, socks_t *socks);
client_t **cli_socks(socks_t *socks, fd_set rfs, client_t **client_socket);
void select_com(fd_set rfs, client_t **client_socket, int sd);

void user(client_t *, int, char **);
void pass(client_t *, int, char **);
void list(client_t *, int, char **);
void cwd(client_t *, int, char **);
void cdup(client_t *, int, char **);
void quit(client_t *, int, char **);
void noop(client_t *, int, char **);
void pwd(client_t *, int, char **);
void dele(client_t *, int, char **);
void help(client_t *, int, char **);
void pasv(client_t *, int, char **);
void retr(client_t *, int, char **);
void stor(client_t *, int, char **);
void port(client_t *, int, char **);

#endif /* !SERVER_H_ */
