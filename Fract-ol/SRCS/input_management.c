/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:21:42 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/26 10:38:23 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_close(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->init, mlx->win);
	if (mlx->img)
		mlx_destroy_image(mlx->init, mlx->img);
	free(mlx->colors);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_pressed(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		ft_close(mlx);
	if (keycode == KEY_P)
	{
		if (mlx->psyche == 1)
			mlx->psyche = 0;
		else
		mlx->psyche = 1;
	}
	if (keycode == KEY_SPACE)
	{
		mlx->zoom = 0.8;
		if (mlx->fractal == 3)
			mlx->color = 0xff4000;
		else
			mlx->color = 0x430070;
		call_fractal(mlx);
	}
	return (0);
}

int	ft_released(int keycode, t_mlx *mlx)
{
	(void) keycode;
	(void) *mlx;
	return (0);
}

int	mouse_wheel(int keycode, int x, int y, t_mlx *mlx)
{
	int	zoom;

	(void)x;
	(void)y;
	if (keycode == ON_MOUSEUP)
		mlx->zoom += 0.5;
	else if (keycode == ON_MOUSEDOWN)
	{
		if (mlx->zoom > 0.8)
		{
			zoom = (mlx->zoom -= 1);
			if (zoom < 0.8)
				mlx->zoom = 0.8;
		}
	}
	if (mlx->psyche == 1)
		mlx->color += 500;
	call_fractal(mlx);
	return (0);
}
