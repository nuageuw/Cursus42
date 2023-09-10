# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/11 19:02:44 by aburnott          #+#    #+#              #
#    Updated: 2023/05/09 10:52:26 by aburnott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
#INCLUDE = includes/philo.h
SRCS = main.c \
		srcs/error.c \
		srcs/utils.c \
		srcs/routine.c \
		srcs/init.c \
		srcs/thread.c
OBJS = $(SRCS:.c=.o)
CC = gcc
SFLAGS = -fsanitize=thread -g
S2FLAGS = -fsanitize=address -g
CFLAGS = -Wall -Werror -Wextra -pthread $(SFLAGS)
#IFLAGS = -I

all: $(NAME)


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Done !"

clean:
	@rm -f $(OBJS)
	@echo "Cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "Full Cleaned"

re: fclean all

.PHONY: all clean fclean re