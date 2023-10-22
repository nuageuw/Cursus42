/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:32:55 by romvan-d          #+#    #+#             */
/*   Updated: 2023/09/13 11:39:07 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 640
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 480
# endif

# ifndef NORTH_SOUTH
#  define NORTH_SOUTH 1
# endif
# ifndef EAST_WEST
#  define EAST_WEST 0
# endif

# ifndef MOV_SPEED
#  define MOV_SPEED 0.1
# endif
# ifndef ROT_SPEED
#  define ROT_SPEED 0.01
# endif

void	raycasting(t_cube *cube);
void	calculate_closest_point_to_wall(t_wall *wall, t_ray *ray);
void	calculate_height_line(t_wall *wall, t_draw *draw);
void	init_camera_position(t_player *player, t_map *map, t_camera *camera);
void	draw_columns(t_cube *cube, int *x_coord);
int		fill_wall_texture(t_cube *cube, int *x_coord, int y);

#endif