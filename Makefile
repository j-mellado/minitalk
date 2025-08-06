# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/06 00:00:00 by jmellado          #+#    #+#              #
#    Updated: 2025/08/06 01:39:14 by jmellado         ###   ########.fr        #
#                                                                             #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client

CC = gcc
CFLAGS = -Wall -Wextra -Werror


SRCS_SERVER = server.c
SRCS_CLIENT = client.c
SRCS_PRINTF = src/ft_printf/ft_printf.c \
              src/ft_printf/ft_printf_hex.c \
              src/ft_printf/ft_printf_number.c \
              src/ft_printf/ft_printf_pointer.c \
              src/ft_printf/ft_printf_string.c \
              src/ft_printf/ft_printf_unsigned.c \
              src/ft_printf/ft_putchar.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o) $(SRCS_PRINTF:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o) $(SRCS_PRINTF:.c=.o)

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	@echo "$(GREEN)Compiling server...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER)
	@echo "$(GREEN)Server compiled successfully!$(RESET)"

$(NAME_CLIENT): $(OBJS_CLIENT)
	@echo "$(GREEN)Compiling client...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT)
	@echo "$(GREEN)Client compiled successfully!$(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	@echo "$(RED)Cleaning executables...$(RESET)"
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re
