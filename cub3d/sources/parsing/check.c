/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:51:10 by aburnott          #+#    #+#             */
/*   Updated: 2023/10/16 17:08:05 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	call_suite(t_cube *cub, char *file)
{
	check_texture(cub);
	store_map(file, cub);
	if (!check_map(cub) || !cub->map.player_found)
		error(cub, "Something went wrong with the map\n", 0);
}

void	check_texture(t_cube *cub)
{
	if (!cub->textures.no)
		error(cub, "Invalid NO texture path\n", 0);
	if (!cub->textures.so)
		error(cub, "Invalid SO texture path\n", 0);
	if (!cub->textures.we)
		error(cub, "Invalid WE texture path\n", 0);
	if (!cub->textures.ea)
		error(cub, "Invalid EA texture path\n", 0);
}

char	*parse_texture(char *path)
{
	int		fd;
	char	**new_path;
	char	*first_path;
	int		i;

	i = 0;
	new_path = ft_split(path, ' ');
	if (new_path[1] != 0)
		return (0);
	fd = open(new_path[0], O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	first_path = ft_strdup(new_path[0], 0, ft_strlen(new_path[0]));
	while(new_path[i])
	{
		free(new_path[i]);
		++i;
	}
	free(new_path);
	return (first_path);
}

void	set_color(t_cube *cub, char *line, int type)
{
	char	**rgb;
	int		i;
	int		current;

	rgb = ft_split(line, ',');
	if (rgb[0] && rgb[1] && rgb[2] && !rgb[3])
	{
		i = 0;
		current = 0;
		while (rgb[i])
		{
			current = ft_atoi(rgb[i], i);
			if (current < 0 || current > 255)
				error(cub, "Invalid RGB value\n", 0);
			if (type == 1)
				cub->map.ceiling = (cub->map.ceiling << 8) + current;
			else
				cub->map.floor = (cub->map.floor << 8) + current;
			i++;
		}
	}
	else
		error(cub, "Invalid RGB value\n", 0);
	ft_free(rgb, 0);
}
