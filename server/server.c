/*
** EPITECH PROJECT, 2020
** server
** File description:
** server
*/

#include "server.h"

void communication(client_t *client)
{
    handle_commands(client);
}

void handle_commands(client_t *client)
{
    char *buff = NULL;
    char **command;
    int lenght = 0;

    buff = get_next_line(client->fd);
    command = str_to_tab(buff, ' ');
    lenght = get_count(buff, ' ') + 1;
    if (get_args(command[0]) == NULL)
        server_response(client, COMMAND_UNKNOWN);
    else
        get_args(command[0])(client, lenght, command);
    free(buff);
}

fptr get_args(char *arg)
{
    static const map commands[] = {
        {"USER", &user}, {"PASS", &pass}, {"LIST", &list},
        {"CWD", &cwd}, {"CDUP", &cdup}, {"QUIT", &quit},
        {"NOOP", &noop}, {"PWD", &pwd}, {"DELE", &dele},
        {"HELP", &help}, {"PASV", &pasv}, {"RETR", &retr},
        {"STOR", &stor}
    };

    for (int i = 0; i != SLEN(commands); i++) {
        if (strcmp(arg, commands[i].key) == 0) {
            return (commands[i].func);
        }
    }
    return (NULL);
}
