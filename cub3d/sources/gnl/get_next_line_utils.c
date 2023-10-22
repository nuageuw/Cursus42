/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:12:57 by aburnott          #+#    #+#             */
/*   Updated: 2023/09/04 17:57:37 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_all(char *save, char *buf)
{
	if (save)
		free(save);
	if (buf)
		free(buf);
	return (0);
}

int	search_n(char *save)
{
	int	i;

	i = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		return (1);
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *save, char *buf, int buf_len)
{
	char	*new_save;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new_save = malloc(sizeof(*new_save) * (ft_strlen(save) + buf_len + 1));
	if (!new_save)
		return (free_all(save, buf));
	if (!save)
		while (buf[++i])
			new_save[i] = buf[i];
	else
	{
		while (save[++i])
			new_save[i] = save[i];
		while (buf[j])
		{
			new_save[i + j] = buf[j];
			j++;
		}
	}
	new_save[i + j] = 0;
	free(save);
	return (new_save);
}
