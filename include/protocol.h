/*
** EPITECH PROJECT, 2020
** protocol
** File description:
** protocol
*/

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

typedef enum code_s {
    SERVICE_READY_SOON = 120,
    DATA_CONNECTION_ALREADY_OPENED = 125,
    OPENING_DATA_CONNECTION = 150,
    OK = 200,
    HELP_MESSAGE = 214,
    SERVICE_READY = 220,
    CLOSING_CONNECTION = 221,
    CLOSING_DATA_CONNECTION = 226,
    ENTERING_PASSIVE_MODE = 227,
    LOGGED_IN = 230,
    FILE_ACTION_OK = 250,
    DIRECTORY_OK = 257,
    NEED_PASSWORD = 331,
    NEED_ACCOUNT_TO_LOGIN = 332,
    COMMAND_UNKNOWN	= 500,
	PARAMETERS_UNKNOWN = 501,
    BAD_COMMAND_SEQUENCE = 503,
    FILE_UNAVAILABLE = 550,
    NOT_LOGGED_IN = 530,
    NEED_PASV_OR_PORT = 425,
} code_t;

typedef struct message_s {
    code_t code;
    char *message;
} message_t;

typedef struct help_s {
    char *command;
    char *message;
} help_t;

#endif /* !PROTOCOL_H_ */
