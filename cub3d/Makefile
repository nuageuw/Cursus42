NAME = cub3D

SRCS_DIR = sources

SRCS = main.c \
		error/error_handler.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		parsing/check_map.c \
		parsing/get_map.c \
		parsing/init.c \
		parsing/parsing.c \
		parsing/check.c \
		utils/utils.c \
		utils/utils2.c \
		utils/ft_split.c \
		rendering/mlx_utils.c \
		rendering/mlx.c\
		rendering/cube_loop.c\
		rendering/render.c\
		rendering/textures.c\
		raycasting/raycasting.c\
		raycasting/drawing.c\
		raycasting/movements.c\
		raycasting/rotations.c\
		raycasting/init_camera.c\

OBJS_DIR = objs

MLX = libmlx.dylib
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./includes -I ./mlx
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit -lm
RM = rm -f

# Colors
RESET = \033[0m
BOLD = \033[1m
DIM = \033[2m
GREEN = \033[32m
YELLOW = \033[33m
CYAN = \033[36m

all: $(NAME)

$(NAME): $(MLX) $(OBJS)
	@echo "$(BOLD)Linking $(CYAN)$@$(RESET)"
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) -o $(NAME)

$(MLX) : 
		make -C mlx
		mv ./mlx/$(MLX) .

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BOLD)Compiling $(YELLOW)$<$(RESET)"
	@$(CC) $(CFLAGS) $(SFLAGS) -c $< -o $@

clean:
	@echo "$(BOLD)Cleaning objects$(RESET)"
	@$(RM) -r $(OBJS_DIR)

fclean: clean
	@echo "$(BOLD)Cleaning $(YELLOW)$(NAME)$(RESET)"
	@$(RM) $(NAME) $(MLX)
	# @make clean -C mlx

re: fclean all

.PHONY: all clean fclean re