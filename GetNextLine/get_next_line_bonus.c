/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:12:28 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/28 14:40:12 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

static char	*read_line(int fd, char *save)
{
	char	*buf;
	int		i;

	i = 0;
	buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_all(save, 0));
	while (!search_n(save))
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
			return (free_all(save, buf));
		if (!i)
			break ;
		buf[i] = 0;
		save = ft_strjoin(save, buf, i);
		if (!save)
			return (0);
	}
	free(buf);
	return (save);
}

static char	*before_n(char *save, int *count)
{
	char	*line;
	int		i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = malloc(sizeof(*line) * i + 1);
	if (!line)
		return (free_all(save, 0));
	*count = i;
	i = 0;
	while (i < *count)
	{
		line[i] = save[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

static char	*after_n(char *save, int count)
{	
	char	*new_save;
	int		i;

	if (count == ft_strlen(save))
		return (free_all(save, 0));
	new_save = malloc(sizeof(*new_save) * (ft_strlen(save) - count) + 1);
	if (!new_save)
		return (free_all(save, 0));
	i = -1;
	while (save[count])
	{
		new_save[++i] = save[count];
		count++;
	}
	new_save[i + 1] = 0;
	free(save);
	return (new_save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;
	int			i;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	save[fd] = read_line(fd, save[fd]);
	if (!save[fd])
		return (0);
	line = before_n(save[fd], &i);
	if (!line)
	{
		save[fd] = 0;
		return (0);
	}
	save[fd] = after_n(save[fd], i);
	return (line);
}
