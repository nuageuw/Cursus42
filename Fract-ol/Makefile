# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 11:09:54 by aburnott          #+#    #+#              #
#    Updated: 2023/01/23 11:48:48 by aburnott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol

SRC_FILE	= fractol.c julia.c mandelbrot.c init.c input_management.c \
				utils.c colors.c ft_parse.c error.c burning.c
SRCS_DIR	= SRCS
OBJSDIR		= objs
INCDIR		= srcs/mlx

SRCS		= $(addprefix ${SRCS_DIR}/, ${SRC_FILE})
OBJS		= $(addprefix ${OBJSDIR}/, $(addsuffix .o, $(basename ${SRC_FILE})))
OBJS_DIR	= $(sort $(dir $(OBJS)))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -O1 -fsanitize=address -g
INCS		= $(foreach d, $(INCDIR), -I$d)

# Minilibx
MLX_DIR		= mlx
MLX_PATH	= ${MLX_DIR}/libmlx.a
MLX			= -framework OpenGL -framework AppKit ${MLX_PATH}

# Rules
${OBJSDIR}/%.o: ${SRCS_DIR}/%.c
			@mkdir -p ${OBJSDIR} ${OBJS_DIR}
			${CC} ${CFLAGS} ${INCS} -c -o $@ $<

all:		${NAME}

${NAME}:	${OBJS}
			@make -C ${MLX_DIR}
			${CC} ${CFLAGS} ${OBJS} ${MLX} -o ${NAME}

clean:
			@make clean -C ${MLX_DIR}
			rm -rf ${OBJSDIR}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re NAME