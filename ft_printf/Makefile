# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 14:09:18 by aburnott          #+#    #+#              #
#    Updated: 2022/10/27 10:32:47 by aburnott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c ft_utils.c 

B_SRCS = ft_printf_bonus.c ft_put_flag_bonus.c ft_utils_bonus.c

OBJS = $(SRCS:.c=.o)

B_OBJS = $(B_SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

all:	$(NAME)

$(NAME):	$(OBJS)
	ar -rcs $(NAME) $(OBJS)

bonus: $(B_OBJS)
	ar -rcs $(NAME) $(B_OBJS)

%.o: %.c
	gcc -c $(CFLAGS) $?

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all bonus clean fclean re