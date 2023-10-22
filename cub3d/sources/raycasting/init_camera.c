/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:13:04 by romvan-d          #+#    #+#             */
/*   Updated: 2023/09/04 16:40:44 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_camera_position_ns(t_player *player, t_map *map,
	t_camera *camera)
{
	if (map->player_orientation == 'N')
	{
		player->director_vector_x = -1;
		player->director_vector_y = 0;
		camera->plane_x = 0;
		camera->plane_y = 0.66;
	}
	if (map->player_orientation == 'S')
	{
		player->director_vector_x = 1;
		player->director_vector_y = 0;
		camera->plane_x = 0;
		camera->plane_y = -0.66;
	}
}

static void	init_camera_position_ew(t_player *player, t_map *map,
	t_camera *camera)
{
	if (map->player_orientation == 'E')
	{
		player->director_vector_x = 0;
		player->director_vector_y = 1;
		camera->plane_x = 0.66;
		camera->plane_y = 0;
	}
	if (map->player_orientation == 'W')
	{
		player->director_vector_x = 0;
		player->director_vector_y = -1;
		camera->plane_x = -0.66;
		camera->plane_y = 0;
	}
}

void	init_camera_position(t_player *player, t_map *map, t_camera *camera)
{
	if (map->player_orientation == 'N' || map->player_orientation == 'S')
		init_camera_position_ns(player, map, camera);
	else if (map->player_orientation == 'E' || map->player_orientation == 'W')
		init_camera_position_ew(player, map, camera);
}
