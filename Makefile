##
## EPITECH PROJECT, 2019
## name
## File description:
## Makefile
##

SRC     =	server/errors.c	\
			server/server.c	\
			server/socket.c  	\
			server/client_side.c	\
			server/commands/user.c	\
			server/commands/pass.c	\
			server/commands/list.c	\
			server/commands/cdup.c	\
			server/commands/cwd.c	\
			server/commands/quit.c	\
			server/commands/noop.c	\
			server/commands/pwd.c	\
			server/commands/dele.c	\
			server/commands/help.c	\
			server/commands/pasv.c	\
			server/commands/retr.c	\
			server/commands/stor.c	\
			server/str_to_tab.c	\
			server/get_next_line.c	\
			server/select.c		\
			server/strclean.c  	\
			server/main.c

OBJ     =	$(SRC:.c=.o)

CC	=	gcc

CPPFLAGS	=	-I include -g3

NAME    =	myftp

# FLAG	=	-W -Wall -Werror -Wextra  -g3 -O3

all:    $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
	rm -f $(shell find $(SOURCEDIR) -name '*.o')
	rm -f $(shell find $(SOURCEDIR) -name '*~')
	rm -f $(shell find $(SOURCEDIR) -name '*.gc*')

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re


