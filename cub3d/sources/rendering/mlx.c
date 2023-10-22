/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 02:29:09 by rom1              #+#    #+#             */
/*   Updated: 2023/10/03 17:38:18 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_put_pixel(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = data->address + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	run_mlx(t_mlx *mlx, t_cube *cube)
{
	mlx_hook(mlx->win, ON_DESTROY, 0, ft_close, cube);
	mlx_hook(mlx->win, ON_KEYDOWN, 0, key_pressed, cube);
	mlx_loop_hook(mlx->init, cube_loop, cube);
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->init);
	return (1);
}

int	init_mlx(t_mlx *mlx, t_cube *cube)
{
	mlx->init = mlx_init();
	if (!mlx->init)
		error(0, "MLX ERROR\n", 0);
	mlx->win = mlx_new_window(mlx->init, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!mlx->win)
		error(0, "MLX ERROR\n", 0);
	mlx->img = mlx_new_image(mlx->init, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!mlx->img)
		error(0, "MLX ERROR\n", 0);
	mlx->address = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->address)
		error(0, "MLX ERROR\n", 0);
	to_xpm(mlx, cube);
	return (run_mlx(mlx, cube));
}
