# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/14 18:15:32 by aburnott          #+#    #+#              #
#    Updated: 2023/01/16 10:37:46 by aburnott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client
S_NAME = server
B_NAME = client_bonus
BS_NAME = server_bonus
SRCS = SRCS/client.c SRCS/utils.c ft_printf/ft_printf.c ft_printf/ft_utils.c
S_SRCS = SRCS/server.c SRCS/utils.c ft_printf/ft_printf.c ft_printf/ft_utils.c
B_SRCS = SRCS/client_bonus.c SRCS/utils.c ft_printf/ft_printf.c ft_printf/ft_utils.c
BS_SRCS = SRCS/server_bonus.c SRCS/utils.c ft_printf/ft_printf.c ft_printf/ft_utils.c
OBJS = $(SRCS:.c=.o)
S_OBJS = $(S_SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)
BS_OBJS = $(BS_SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME) $(S_NAME)

bonus: $(B_OBJS) $(BS_OBJS)
	@$(CC) $(CFLAGS) $(B_OBJS) -o $(B_NAME)
	@echo "Client Bonus Compiled"
	@$(CC) $(CFLAGS) $(BS_OBJS) -o $(BS_NAME)
	@echo "Server Bonus Compiled"

$(S_NAME): $(S_OBJS)
	@$(CC) $(CFLAGS) $(S_OBJS) -o $(S_NAME)
	@echo "Server Compiled"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Client Compiled"

clean:
	@rm -f $(OBJS)
	@rm -f $(S_OBJS)
	@rm -f $(B_OBJS)
	@rm -f $(BS_OBJS)
	@echo "Cleaned"
fclean: clean
	@rm -f $(NAME)
	@rm -f $(S_NAME)
	@rm -f $(B_NAME)
	@rm -f $(BS_NAME)
	@echo "Full Cleaned"
re: fclean all
.PHONY: all clean fclean re