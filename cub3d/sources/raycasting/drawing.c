/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:49:16 by romvan-d          #+#    #+#             */
/*   Updated: 2023/09/04 18:30:36 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_closest_point_to_wall(t_wall *wall, t_ray *ray)
{
	if (wall->which_side_hit == EAST_WEST)
		wall->shortest_dist_to_wall = (ray->move_to_next_x
				- ray->distance_to_next_x);
	else
		wall->shortest_dist_to_wall = (ray->move_to_next_y
				- ray->distance_to_next_y);
}

void	calculate_height_line(t_wall *wall, t_draw *draw)
{
	draw->line_height = abs((int)(SCREEN_HEIGHT / wall->shortest_dist_to_wall));
	draw->start_pos = -draw->line_height / 2 + (double)SCREEN_HEIGHT / 2;
	if (draw->start_pos < 0)
		draw->start_pos = 0;
	draw->end_pos = draw->line_height / 2 + (double)SCREEN_HEIGHT / 2;
	if (draw->end_pos >= SCREEN_HEIGHT)
		draw->end_pos = SCREEN_HEIGHT - 1;
}

void	fill_floor_and_ceiling(t_cube *cube, int *x_coord, int y)
{
	if (cube->draw.end_pos < 0)
		cube->draw.end_pos = SCREEN_HEIGHT;
	y = cube->draw.end_pos;
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_put_pixel(&cube->mlx, *x_coord, y, cube->map.floor);
		my_mlx_put_pixel(&cube->mlx, *x_coord, SCREEN_HEIGHT - y - 1,
			cube->map.ceiling);
		++y;
	}
}

void	draw_columns(t_cube *cube, int *x_coord)
{
	int	y;

	y = 0;
	if (cube->wall.which_side_hit == EAST_WEST)
	{
		cube->textures.wall_x = cube->map.player_y
			+ cube->wall.shortest_dist_to_wall * cube->ray.direction_y;
	}
	else
		cube->textures.wall_x = cube->map.player_x
			+ cube->wall.shortest_dist_to_wall * cube->ray.direction_x;
	cube->textures.wall_x -= floor(cube->textures.wall_x);
	cube->textures.x = (int)(cube->textures.wall_x
			* (double)cube->textures.width);
	if (cube->wall.which_side_hit == NORTH_SOUTH && cube->ray.direction_y < 0)
		cube->textures.x = cube->textures.width - cube->textures.x - 1;
	if (cube->wall.which_side_hit == EAST_WEST && cube->ray.direction_x > 0)
		cube->textures.x = cube->textures.width - cube->textures.x - 1;
	y += fill_wall_texture(cube, x_coord, y);
	fill_floor_and_ceiling(cube, x_coord, y);
}
