/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:05:41 by romvan-d          #+#    #+#             */
/*   Updated: 2023/10/03 17:37:27 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close(t_cube *cube)
{
	if (cube->mlx.win)
		mlx_destroy_window(cube->mlx.init, cube->mlx.win);
	if (cube->mlx.img)
		mlx_destroy_image(cube->mlx.init, cube->mlx.img);
	if (cube->map.map)
		ft_free_end(cube);
	exit(1);
	return (0);
}

int	key_pressed(int keycode, t_cube *cube)
{
	if (keycode == KEY_ESC)
		ft_close(cube);
	else if (keycode == KEY_W)
		forward_movement(cube);
	else if (keycode == KEY_S)
		backward_movement(cube);
	else if (keycode == KEY_A)
		left_movement(cube);
	else if (keycode == KEY_D)
		right_movement(cube);
	else if (keycode == KEY_LEFT)
		rotate_left(cube);
	else if (keycode == KEY_RIGHT)
		rotate_right(cube);
	return (0);
}

static void	check_size(int *width, int *height)
{
	if (*width != 64)
		error(0, "Invalid texture width\n", 0);
	if (*height != 64)
		error(0, "Invalid texture height\n", 0);
}

static void	to_xpm_suite(t_cube *cube)
{
	int	x;
	int	y;
	int	z;

	cube->textures.stored[0] = mlx_get_data_addr(cube->textures.wall_no,
			&x, &y, &z);
	if (!cube->textures.stored[0])
		error(0, "MLX ERROR\n", 0);
	cube->textures.stored[1] = mlx_get_data_addr(cube->textures.wall_so,
			&x, &y, &z);
	if (!cube->textures.stored[1])
		error(0, "MLX ERROR\n", 0);
	cube->textures.stored[2] = mlx_get_data_addr(cube->textures.wall_ea,
			&x, &y, &z);
	if (!cube->textures.stored[2])
		error(0, "MLX ERROR\n", 0);
	cube->textures.stored[3] = mlx_get_data_addr(cube->textures.wall_we,
			&x, &y, &z);
	if (!cube->textures.stored[3])
		error(0, "MLX ERROR\n", 0);
}

void	to_xpm(t_mlx *mlx, t_cube *cube)
{
	cube->textures.wall_ea = mlx_xpm_file_to_image(mlx->init, cube->textures.ea,
			&cube->textures.width, &cube->textures.height);
	check_size(&cube->textures.width, &cube->textures.height);
	cube->textures.wall_no = mlx_xpm_file_to_image(mlx->init, cube->textures.no,
			&cube->textures.width, &cube->textures.height);
	check_size(&cube->textures.width, &cube->textures.height);
	cube->textures.wall_so = mlx_xpm_file_to_image(mlx->init, cube->textures.so,
			&cube->textures.width, &cube->textures.height);
	check_size(&cube->textures.width, &cube->textures.height);
	cube->textures.wall_we = mlx_xpm_file_to_image(mlx->init, cube->textures.we,
			&cube->textures.width, &cube->textures.height);
	check_size(&cube->textures.width, &cube->textures.height);
	check_value(cube);
	to_xpm_suite(cube);
}
