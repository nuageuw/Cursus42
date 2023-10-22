/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:26:09 by romvan-d          #+#    #+#             */
/*   Updated: 2023/09/22 16:43:34 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	forward_movement(t_cube *cube)
{
	int	new_pos_x;
	int	new_pos_y;

	new_pos_x = cube->map.player_x + (cube->player.director_vector_x + 0.01)
		* MOV_SPEED;
	new_pos_y = cube->map.player_y + (cube->player.director_vector_y + 0.01)
		* MOV_SPEED;
	if (cube->map.map[new_pos_x][(int)cube->map.player_y] != '1')
	{
		cube->map.player_x += cube->player.director_vector_x * MOV_SPEED;
	}
	if (cube->map.map[(int)(cube->map.player_x)][new_pos_y] != '1')
	{
		cube->map.player_y += cube->player.director_vector_y * MOV_SPEED;
	}
}

void	backward_movement(t_cube *cube)
{
	int	new_pos_x;
	int	new_pos_y;

	new_pos_x = cube->map.player_x - (cube->player.director_vector_x + 0.01)
		* MOV_SPEED;
	new_pos_y = cube->map.player_y - (cube->player.director_vector_y + 0.01)
		* MOV_SPEED;
	if (cube->map.map[new_pos_x][(int)cube->map.player_y] != '1')
	{
		cube->map.player_x -= cube->player.director_vector_x * MOV_SPEED;
	}
	if (cube->map.map[(int)(cube->map.player_x)][new_pos_y] != '1')
	{
		cube->map.player_y -= cube->player.director_vector_y * MOV_SPEED;
	}
}

void	left_movement(t_cube *cube)
{
	int	new_pos_x;
	int	new_pos_y;

	new_pos_x = cube->map.player_x - (cube->camera.plane_x + 0.01) * MOV_SPEED;
	new_pos_y = cube->map.player_y - (cube->camera.plane_y + 0.01) * MOV_SPEED;
	if (cube->map.map[new_pos_x][(int)cube->map.player_y] != '1')
	{
		cube->map.player_x -= cube->camera.plane_x * MOV_SPEED;
	}
	if (cube->map.map[(int)cube->map.player_x][new_pos_y] != '1')
	{
		cube->map.player_y -= cube->camera.plane_y * MOV_SPEED;
	}
}

void	right_movement(t_cube *cube)
{
	int	new_pos_x;
	int	new_pos_y;

	new_pos_x = cube->map.player_x + (cube->camera.plane_x + 0.01) * MOV_SPEED;
	new_pos_y = cube->map.player_y + (cube->camera.plane_y + 0.01) * MOV_SPEED;
	if (cube->map.map[new_pos_x][(int)cube->map.player_y] != '1')
	{
		cube->map.player_x += cube->camera.plane_x * MOV_SPEED;
	}
	if (cube->map.map[(int)cube->map.player_x][new_pos_y] != '1')
	{
		cube->map.player_y += cube->camera.plane_y * MOV_SPEED;
	}
}
