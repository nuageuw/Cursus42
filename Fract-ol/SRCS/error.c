/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:00 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/26 10:35:01 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	print_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
}

void	display_option(void)
{
	ft_putstr("Name: mandelbrot, julia, burning");
	ft_putstr("Option:");
	ft_putstr("\t- [julia re]: Default: -0.4");
	ft_putstr("\t- [julia im]: Default: 0.6");
	ft_putstr("Exemple with option for julia:");
	ft_putstr("./fractol julia -0.285 0.01");
	ft_putstr("./fractol julia 0.3 0.5");
	ft_putstr("./fractol julia -0.8 0.156");
}

void	display_command(void)
{
	ft_putstr("==== Available Commands ====");
	ft_putstr("Use mouse wheel to zoom.\n");
	ft_putstr("==== Control ====");
	ft_putstr(" - Space to reset the fractal.");
	ft_putstr(" - P to run psychedelique mode.");
	ft_putstr(" - Escape or Cross to exit.");
}
