/*
** EPITECH PROJECT, 2020
** client_side
** File description:
** client_side
*/

#include "server.h"

client_t *init_client(char *path, char *ip)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        exit (84);
    client->username = NULL;
    client->password = NULL;
    client->ip = ip;
    client->last_command = "EMPTY";
    client->quit = false;
    client->is_log = false;
    client->fd = 0;
    client->fd_mod = 0;
    client->passv_port = 0;
    client->path = path;
    client->is_pasv = false;
    chdir(path);
    return (client);
}

client_t **tab_client(char *path, char *ip)
{
    client_t **client_tab = malloc(sizeof(client_t *) * MAXCLIENT);

    for (int i = 0; i <= MAXCLIENT; ++i) {
        client_tab[i] = init_client(path, ip);
    }
    return (client_tab);
}

char *get_message(code_t code)
{
    static const message_t message[] = {
        {331, "User name okay, need password."},
        {230, "User logged in, proceed."}, {503, "Bad command sequence"},
        {220, "Service ready"}, {501, "Bad parameters"},
        {250, "Requested file action okay, completed."},
        {200, "Command okay"}, {550, "File unavailable"},
        {500, "Command unknown"}, {214, "Help"}, {530, "Not logged in"},
        {221, "Bye"}, {425, "Need pasv or port"}, {150, "opening connection"},
        {226, "closing data connection"}
    };

    for (int i = 0; i != SLEN(message); i++) {
        if (code == message[i].code) {
            return (message[i].message);
        }
    }
    return (NULL);
}

char *get_help(char *command)
{
    static const help_t help[] = {
        {"USER", "Specify user for authentication"},
        {"PASS", "Specify password for authentication"},
        {"LIST", "List files in the current working directory "},
        {"CWD", "Change working directory"},
        {"CDUP", "Change working directory to parent directory"},
        {"QUIT", "Disconnection"},
        {"NOOP", "Do nothing"},
        {"PWD", "Print working directory"},
        {"DELE", "Delete file on the server"}
    };
    for (int i = 0; i != SLEN(help); i++) {
        if (strcmp(command, help[i].command) == 0) {
            return (help[i].message);
        }
    }
    return (NULL);
}

int server_response(client_t *client, code_t code)
{
    if (get_message(code) != NULL)
        dprintf(client->fd, "%d : %s\n", code, get_message(code));
    return (0);
}