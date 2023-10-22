/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:50:40 by romvan-d          #+#    #+#             */
/*   Updated: 2023/09/13 11:16:04 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map(t_cube *cube)
{
	cube->map.map = 0;
	cube->map.player_orientation = 0;
	cube->map.start_line = 0;
	cube->map.x = 0;
	cube->map.y = 0;
	cube->map.player_found = 0;
	cube->map.player_x = 0;
	cube->map.player_y = 0;
	cube->map.player_patch = 0;
	cube->map.map_error = 0;
	cube->map.floor = 0;
	cube->map.ceiling = 0;
}

static void	init_player_and_camera_and_ray(t_cube *cube)
{
	cube->player.current_square_x = 0;
	cube->player.current_square_y = 0;
	cube->camera.current_x = 0;
	cube->ray.direction_x = 0;
	cube->ray.direction_y = 0;
	cube->ray.move_to_next_x = 0;
	cube->ray.move_to_next_y = 0;
	cube->ray.distance_to_next_x = 0;
	cube->ray.distance_to_next_y = 0;
	cube->ray.step_in_x = 0;
	cube->ray.step_in_y = 0;
}

static void	init_textures(t_cube *cube)
{
	cube->textures.stored[0] = NULL;
	cube->textures.stored[1] = NULL;
	cube->textures.stored[2] = NULL;
	cube->textures.stored[3] = NULL;
	cube->textures.no = NULL;
	cube->textures.so = NULL;
	cube->textures.we = NULL;
	cube->textures.ea = NULL;
	cube->textures.choice = 0;
	cube->textures.colour = 0;
	cube->textures.f = 0;
	cube->textures.c = 0;
	cube->textures.x = 0;
	cube->textures.y = 0;
	cube->textures.height = 64;
	cube->textures.width = 64;
	cube->textures.wall_x = 0;
}

static void	init_walls_and_drawings(t_cube *cube)
{
	cube->wall.shortest_dist_to_wall = 0;
	cube->wall.is_hit = 0;
	cube->wall.which_side_hit = 0;
	cube->draw.end_pos = 0;
	cube->draw.start_pos = 0;
	cube->draw.line_height = 0;
}

void	init_struc(char *av)
{
	t_cube	cube;

	init_map(&cube);
	init_player_and_camera_and_ray(&cube);
	init_textures(&cube);
	init_walls_and_drawings(&cube);
	check_file(av, &cube);
	init_camera_position(&cube.player, &cube.map, &cube.camera);
	init_mlx(&cube.mlx, &cube);
}
