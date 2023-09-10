/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:26:55 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/20 12:09:04 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	ft_color(t_mlx *f, int n, int x, int y)
{
	int	color;

	if (n >= 0 && n <= MAX_ITERATIONS - 1)
		color = f->color * n;
	else
		color = 0x000000;
	f->addr[x * 4 + y * WIDTH * 4] = color;
	f->addr[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
	f->addr[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
	f->addr[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
}

void	ft_set_colors(t_mlx *f, int color)
{
	int	i;
	int	rgb[3];

	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 0) & 0xFF;
	i = -1;
	while (rgb[0] < 0x33 || rgb[1] < 0x33 || rgb[2] < 0x33)
	{
		if (rgb[0] != 0xFF)
			rgb[0]++;
		if (rgb[1] != 0xFF)
			rgb[1]++;
		if (rgb[2] != 0xFF)
			rgb[2]++;
	}
	while (++i < MAX_ITERATIONS)
	{
		f->colors[i] = 0;
		rgb[0] -= i % 0xFF;
		rgb[1] -= i % 0xFF;
		rgb[2] -= i % 0xFF;
		f->colors[i] = 0xFF << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	}
	f->colors[MAX_ITERATIONS - 1] = 0;
}
