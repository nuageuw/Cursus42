/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:27:23 by romvan-d          #+#    #+#             */
/*   Updated: 2023/09/04 18:36:01 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_wall_texture(t_cube *cube, int *x_coord, int y)
{
	y = cube->draw.start_pos;
	while (y < cube->draw.end_pos)
	{
		cube->textures.y = (int)(y * 2 - SCREEN_HEIGHT + cube->draw.line_height)
			* (cube->textures.height / 2) / cube->draw.line_height;
		if (cube->wall.which_side_hit == NORTH_SOUTH
			&& cube->ray.direction_y > 0)
			cube->textures.choice = 0;
		if (cube->wall.which_side_hit == NORTH_SOUTH
			&& cube->ray.direction_y < 0)
			cube->textures.choice = 1;
		if (cube->wall.which_side_hit == EAST_WEST && cube->ray.direction_x > 0)
			cube->textures.choice = 2;
		if (cube->wall.which_side_hit == EAST_WEST && cube->ray.direction_x < 0)
			cube->textures.choice = 3;
		cube->textures.colour = ((unsigned int *)cube
				->textures.stored[cube->textures.choice])
		[cube->textures.x + cube->textures.y * cube->textures.width];
		my_mlx_put_pixel(&cube->mlx, *x_coord, y, cube->textures.colour);
		++y;
	}
	return (y);
}
