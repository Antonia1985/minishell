NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./include -I./libft/include -Ignl -fsanitize=address -g
LDFLAGS = -lreadline -lhistory
LIBFT = ./libft/libft.a
SRC = src/main.c src/executor.c src/dispatcher.c \
	src/ft_cd.c src/ft_exit.c src/ft_pwd.c\
	src/ft_export.c src/ft_unset.c src/ft_env.c src/ft_echo.c \
	src/shared_fun.c src/converter.c src/signals_handler.c

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
