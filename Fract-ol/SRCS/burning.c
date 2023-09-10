/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:25:37 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/26 10:31:08 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static int	ft_iteration(double const_i, double const_r)
{
	double	z_real_n;
	double	z_imag_n;
	double	z_real;
	double	z_imag;
	int		i;

	z_real_n = 0;
	z_imag_n = 0;
	z_real = 0;
	z_imag = 0;
	i = 0;
	while ((z_real_n * z_real_n + z_imag_n * z_imag_n) < 4
		&& i < MAX_ITERATIONS)
	{
		z_real_n = z_real * z_real - z_imag * z_imag + const_i;
		z_imag_n = 2 * fabs(z_real * z_imag) + const_r;
		z_real = z_real_n;
		z_imag = z_imag_n;
		++i;
	}
	return (i);
}

void	draw_burning(t_mlx *mlx)
{
	double	x;
	double	y;
	double	const_i;
	double	const_r;
	int		i;

	y = 0;
	mlx_clear_window(mlx->init, mlx->win);
	while (y < HEIGHT)
	{
		x = 0;
		const_i = (y - HEIGHT / 2) / (0.3 * mlx->zoom * HEIGHT);
		while (x < WIDTH)
		{
			const_r = 1.5 * (x - WIDTH / 2) / (0.3 * mlx->zoom * WIDTH);
			i = ft_iteration(const_i, const_r);
			ft_color(mlx, i, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
}
