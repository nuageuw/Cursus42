/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:37:13 by romvan-d          #+#    #+#             */
/*   Updated: 2023/09/14 11:33:20 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
	char	*address;
	int		endian;
	int		bits_per_pixel;
	int		line_length;
}	t_mlx;

typedef struct s_player
{
	double	director_vector_x;
	double	director_vector_y;
	int		current_square_x;
	int		current_square_y;
}	t_player;

typedef struct s_camera
{
	double	plane_x;
	double	plane_y;
	double	current_x;
}	t_camera;

typedef struct s_ray
{
	double	direction_x;
	double	direction_y;
	double	move_to_next_x;
	double	move_to_next_y;
	double	distance_to_next_x;
	double	distance_to_next_y;
	int		step_in_x;
	int		step_in_y;
}	t_ray;

typedef struct s_wall
{
	double	shortest_dist_to_wall;
	int		is_hit;
	int		which_side_hit;
}	t_wall;

typedef struct s_draw
{
	int	line_height;
	int	start_pos;
	int	end_pos;
}	t_draw;

typedef struct s_map
{
	char			**map;
	char			player_orientation;
	int				start_line;
	int				x;
	int				y;
	int				player_found;
	double			player_x;
	double			player_y;
	int				map_error;
	int				player_patch;
	unsigned int	floor;
	unsigned int	ceiling;
}	t_map;

typedef struct s_textures
{
	double	wall_x;
	int		x;
	int		y;
	char	*stored[4];
	int		width;
	int		height;
	int		choice;
	int		colour;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	void	*wall_no;
	void	*wall_so;
	void	*wall_we;
	void	*wall_ea;
}	t_textures;

typedef struct s_cube
{
	t_player	player;
	t_camera	camera;
	t_ray		ray;
	t_wall		wall;
	t_draw		draw;
	t_mlx		mlx;
	t_textures	textures;
	t_map		map;
}	t_cube;

#endif