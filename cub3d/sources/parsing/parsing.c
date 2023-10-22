/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:22:06 by aburnott          #+#    #+#             */
/*   Updated: 2023/10/16 17:11:37 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(char *line, int type, t_cube *cub, int start)
{
	char *tmp;

	if (type == 1)
	{
		tmp = ft_strdup(line, start + 2, ft_strlen(line));
		set_color(cub, tmp, 2);
		free(tmp);
	}
	else if (type == 2)
	{
		tmp = ft_strdup(line, start + 2, ft_strlen(line));
		set_color(cub, tmp, 1);
		free(tmp);
	}
	return (0);
}

int	get_texture(char *line, int type, t_cube *cub, int start)
{
	char *tmp;

	tmp = ft_strdup(line, start + 3, ft_strlen(line) - 1);
	if (type == 1)
	{
		cub->textures.no = parse_texture(tmp);
	}
	else if (type == 2)
	{
		cub->textures.so = parse_texture(tmp);
	}
	else if (type == 3)
	{
		cub->textures.we = parse_texture(tmp);
	}
	else if (type == 4)
	{
		cub->textures.ea = parse_texture(tmp);
	}
	free(tmp);
	return (0);
}

static void	continue_catch(char *line, t_cube *cub, int res, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
		res = get_texture(line, 1, cub, i);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		res = get_texture(line, 2, cub, i);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		res = get_texture(line, 3, cub, i);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		res = get_texture(line, 4, cub, i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		res = get_color(line, 1, cub, i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		res = get_color(line, 2, cub, i);
	else if ((line[i] != '\n') || res == -1)
	{
		error(cub, "Something went wrong with map file\n", 0);
	}
}

void	catch_textures(char *line, t_cube *cub, int line_count)
{
	int		res;
	int		i;

	res = 0;
	i = 0;
	if (line[0] == ' ' || line[0] == '1')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
		{
			if (cub->map.start_line == 0)
				cub->map.start_line = line_count;
			res = get_map_size(line, cub);
		}
		else
			continue_catch(line, cub, res, i);
	}
	else
		continue_catch(line, cub, res, i);
}

int	check_file(char *file, t_cube *cub)
{
	int		fd;
	int		line_count;
	char	*line;

	line = "";
	line_count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error(cub, "Can't open file\n", 1);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		line_count++;
		catch_textures(line, cub, line_count);
		free(line);
	}
	close(fd);
	call_suite(cub, file);
	return (0);
}
