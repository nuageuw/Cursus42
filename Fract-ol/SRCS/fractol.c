/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:47:24 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/26 10:28:00 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	call_fractal(t_mlx *mlx)
{
	if (mlx->fractal == 1)
		mandelbrot(mlx);
	else if (mlx->fractal == 2)
		julia(mlx);
	else if (mlx->fractal == 3)
		draw_burning(mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac >= 2)
	{
		ft_parsing(av, ac, &mlx);
		if (mlx.fractal == 2)
			init_fractal(av, ac, &mlx);
		if (!init_mlx(&mlx))
			exit(EXIT_FAILURE);
		call_fractal(&mlx);
		display_command();
		mlx_hook(mlx.win, ON_DESTROY, 0, ft_close, &mlx);
		mlx_hook(mlx.win, ON_KEYDOWN, 0, key_pressed, &mlx);
		mlx_hook(mlx.win, ON_KEYUP, 0, ft_released, &mlx);
		mlx_mouse_hook(mlx.win, mouse_wheel, &mlx);
		mlx_put_image_to_window(mlx.init, mlx.win, mlx.img, 0, 0);
		mlx_loop(mlx.init);
	}
	else
	{
		print_error("Error. Missing arguments.\n");
		display_option();
	}
	return (0);
}
