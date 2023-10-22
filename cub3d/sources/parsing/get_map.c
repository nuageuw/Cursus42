/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:33:24 by aburnott          #+#    #+#             */
/*   Updated: 2023/09/13 14:09:11 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_current_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	return (line);
}

static int	insert_map(t_cube *cub, int fd, int i, char *line)
{
	while (i < cub->map.y)
	{
		cub->map.map[cub->map.y - 1] = ft_malloc(sizeof(char) * cub->map.x);
		i++;
	}
	i = 0;
	while (i < cub->map.start_line - 1)
	{
		line = read_current_line(fd);
		if (!line)
			return (-1);
		free(line);
		i++;
	}
	i = 0;
	while (i < cub->map.y)
	{
		line = read_current_line(fd);
		if (!line)
			return (-1);
		cub->map.map[i] = ft_strdup_modif(line, 0, (cub->map.x - 1));
		free(line);
		i++;
	}
	return (0);
}

int	store_map(char *file, t_cube *cub)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	cub->map.map = ft_malloc(sizeof(char *) * cub->map.y);
	if (insert_map(cub, fd, i, line) == -1)
		return (-1);
	close(fd);
	cub->map.map[(int)cub->map.player_y][(int)cub->map.player_x] = '0';
	ft_swap_double(&cub->map.player_x, &cub->map.player_y);
	return (0);
}

int	get_map_size(char *line, t_cube *cub)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'W' || line[i] == 'E')
		{
			cub->map.player_x = i;
			cub->map.player_y = cub->map.y;
			cub->map.player_found = 1;
			cub->map.player_orientation = line[i];
		}
		i++;
	}
	if (line[i - 2] == '1' || line[i - 1])
	{
		cub->map.y += 1;
		if (i > cub->map.x)
			cub->map.x = i;
		return (0);
	}
	return (-1);
}
