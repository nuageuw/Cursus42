/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:36:48 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/26 10:14:04 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static int	ft_iteration(double z_re, double z_im, t_mlx *mlx)
{
	int		iteration;
	double	new_re;
	double	new_im;

	iteration = 0;
	while (z_re * z_re + z_im * z_im < 4 && iteration < MAX_ITERATIONS)
	{
		new_re = z_re * z_re - z_im * z_im + mlx->c_re;
		new_im = 2 * z_re * z_im + mlx->c_im;
		z_re = new_re;
		z_im = new_im;
		iteration++;
	}
	return (iteration);
}

void	julia(t_mlx *mlx)
{
	int		y;
	int		x;
	double	z_re;
	double	z_im;
	int		iteration;

	y = 0;
	mlx_clear_window(mlx->init, mlx->win);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			z_re = 1.5 * (x - WIDTH / 2) / (0.5 * mlx->zoom * WIDTH);
			z_im = (y - HEIGHT / 2) / (0.5 * mlx->zoom * HEIGHT);
			iteration = ft_iteration(z_re, z_im, mlx);
			ft_color(mlx, iteration, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
}
