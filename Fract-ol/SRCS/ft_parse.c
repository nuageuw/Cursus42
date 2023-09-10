/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:35:24 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/23 15:46:13 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_parsing(char **av, int ac, t_mlx *mlx)
{
	(void) ac;
	if (!ft_strncmp(av[1], "mandelbrot", 10))
		mlx->fractal = 1;
	else if (!ft_strncmp(av[1], "julia", 5))
	{
		mlx->fractal = 2;
		if (ac == 3 || ac > 4)
		{
			print_error("Error with number of arguments.\n");
			display_option();
			exit(EXIT_FAILURE);
		}
	}
	else if (!ft_strncmp(av[1], "burning", 6))
		mlx->fractal = 3;
	else
	{
		print_error("Wrong fractal name.\n");
		ft_putstr("Usage: ./fractol <name> [option1] [option2] ...");
		display_option();
		exit(EXIT_FAILURE);
	}
	return (1);
}
