/*
** EPITECH PROJECT, 2020
** strtotab
** File description:
** str_to_tab
*/

#include "server.h"

char *remove_n(char *str)
{
    int j, n = strlen(str);

    for (int i = j = 0; i < n; i++) {
        if (str[i] != '\n')
            str[j++] = str[i];
    }
    str[j] = '\0';
    return (str);
}

int get_count(char *line, char delim)
{
    int count = 0;

    for (int i = 0; line[i] != '\0'; i++)
        count += (line[i] == delim ? 1 : 0);
    return (count);
}

static char **malloc_tab(char *line, char delim)
{
    int count = get_count(line, delim) + 1;
    char **tab = malloc(sizeof(char *) * (count + 1));

    if (tab == NULL)
        exit(84);
    for (int i = 0; i != count; i++) {
        tab[i] = calloc(1, sizeof(char) * (strlen(line) + 1));
        if (tab[i] == NULL)
            exit(84);
    }
    return (tab);
}

char **str_to_tab(char *line, char delim)
{
    char **args = malloc_tab(line, delim);
    int index[] = {0 , 0, 0};

    for (; line[index[2]] != '\0' && line[index[2]] != '\r' &&
        line[index[2]] != '\n'; index[2]++, index[1]++) {
        if (line[index[2]] == delim) {
            index[0]++;
            index[1] = -1;
        } else
            args[index[0]][index[1]] = line[index[2]];
    }
    args[index[0] + 1] = NULL;
    return (args);
}
