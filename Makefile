NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./include -I./libft/include -fsanitize=address -g
LDFLAGS = -lreadline -lhistory
LIBFT = ./libft/libft.a
SRC = src/main.c src/externals_executor.c src/builtin_executor.c src/pipe_executor.c\
	src/ft_cd.c src/ft_exit.c src/ft_pwd.c\
	src/ft_export.c src/ft_unset.c src/ft_env.c src/ft_echo.c \
	src/shared_fun.c src/converter.c src/signals_handler.c \
	src/here_doc.c src/redirections.c src/sort_envp.c src/linked_lists_handle.c \
	src/parser.c 

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
