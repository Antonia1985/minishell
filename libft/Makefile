# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 19:19:19 by apavlopo          #+#    #+#              #
#    Updated: 2024/11/12 19:22:04 by apavlopo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc                         
CFLAGS = -Wall -Wextra -Werror -I./include
AR = ar
ARFLAGS = rcs
SRC = src/ft_atoi.c	src/ft_atol.c src/ft_bzero.c src/ft_calloc.c src/ft_isalnum.c src/ft_isalpha.c \
src/ft_isascii.c src/ft_isdigit.c src/ft_isprint.c src/ft_itoa.c src/ft_memchr.c src/ft_memcmp.c src/ft_memcpy.c \
src/ft_memmove.c src/ft_memset.c src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c \
src/ft_putstr_fd.c src/ft_realloc.c src/ft_split.c src/ft_strchr.c src/ft_strcmp.c src/ft_strdup.c src/ft_striteri.c src/ft_strjoin.c \
src/ft_strlcat.c src/ft_strlcpy.c src/ft_strlen.c src/ft_strmapi.c src/ft_strncmp.c src/ft_strnstr.c \
src/ft_strrchr.c src/ft_strtrim.c src/ft_substr.c src/ft_tolower.c src/ft_toupper.c\
src/ft_printf.c src/ft_putchar.c src/ft_print_ptr.c src/ft_putstr.c src/ft_print_nbr.c src/ft_print_unsigned_dec.c src/ft_dec_to_hex.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
