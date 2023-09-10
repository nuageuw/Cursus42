/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:56:34 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/23 16:16:20 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	init_colors(t_mlx *mlx)
{
	if (mlx->fractal == 3)
		mlx->color = 0xff4000;
	else
		mlx->color = 0x430070;
	mlx->colors = (int *)malloc(sizeof(int) * MAX_ITERATIONS + 1);
	if (!mlx->color)
		return (0);
	ft_set_colors(mlx, mlx->color);
	mlx->zoom = 0.8;
	mlx->psyche = 0;
	return (1);
}

int	init_mlx(t_mlx *mlx)
{	
	int	endian;
	int	bits_per_pixel;
	int	line_lenght;

	mlx->init = mlx_init();
	if (!mlx->init)
		return (0);
	mlx->win = mlx_new_window(mlx->init, WIDTH, HEIGHT, "Fract-ol");
	if (!mlx->win)
		return (0);
	mlx->img = mlx_new_image(mlx->init, WIDTH, HEIGHT);
	if (!mlx->img)
		return (0);
	mlx->addr = mlx_get_data_addr(mlx->img, &bits_per_pixel, &line_lenght,
			&endian);
	return (init_colors(mlx));
}

int	init_fractal(char **av, int ac, t_mlx *mlx)
{
	int	check;

	check = 0;
	if (ac == 4)
	{
		if (av[2])
			mlx->c_re = ft_atof(av[2], &check);
		if (av[3])
			mlx->c_im = ft_atof(av[3], &check);
		if (check == 1)
		{
			print_error("Invalid option.\n");
			display_option();
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		mlx->c_re = -0.4;
		mlx->c_im = 0.6;
	}
	return (0);
}
