/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:10:32 by romvan-d          #+#    #+#             */
/*   Updated: 2023/08/30 12:50:14 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_cube *cube)
{
	double	old_director_vector_x;
	double	old_camera_plane_x;

	old_director_vector_x = cube->player.director_vector_x;
	old_camera_plane_x = cube->camera.plane_x;
	cube->player.director_vector_x = cube->player.director_vector_x
		* cos(ROT_SPEED) - cube->player.director_vector_y * sin(ROT_SPEED);
	cube->player.director_vector_y = old_director_vector_x * sin(ROT_SPEED)
		+ cube->player.director_vector_y * cos(ROT_SPEED);
	cube->camera.plane_x = cube->camera.plane_x * cos(ROT_SPEED)
		- cube->camera.plane_y * sin(ROT_SPEED);
	cube->camera.plane_y = old_camera_plane_x * sin (ROT_SPEED)
		+ cube->camera.plane_y * cos(ROT_SPEED);
}

void	rotate_right(t_cube *cube)
{
	double	old_director_vector_x;
	double	old_camera_plane_x;

	old_director_vector_x = cube->player.director_vector_x;
	old_camera_plane_x = cube->camera.plane_x;
	cube->player.director_vector_x = cube->player.director_vector_x
		* cos(-ROT_SPEED) - cube->player.director_vector_y * sin(-ROT_SPEED);
	cube->player.director_vector_y = old_director_vector_x
		* sin(-ROT_SPEED) + cube->player.director_vector_y * cos(-ROT_SPEED);
	cube->camera.plane_x = cube->camera.plane_x * cos(-ROT_SPEED)
		- cube->camera.plane_y * sin(-ROT_SPEED);
	cube->camera.plane_y = old_camera_plane_x * sin (-ROT_SPEED)
		+ cube->camera.plane_y * cos(-ROT_SPEED);
}
