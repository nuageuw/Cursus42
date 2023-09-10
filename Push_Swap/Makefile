# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 12:07:55 by aburnott          #+#    #+#              #
#    Updated: 2023/01/12 10:40:54 by aburnott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
SRCS = SRCS/push_swap.c SRCS/stack_utils/init_stack.c \
	SRCS/stack_utils/stack_push.c SRCS/utils/utils.c SRCS/utils/ft_split.c \
	SRCS/operations/p_operation.c SRCS/operations/s_operation.c \
	SRCS/operations/r_operation.c SRCS/operations/rr_operation.c \
	SRCS/operations/swap.c SRCS/algo/small_sort.c SRCS/algo/algo.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re