/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:00:24 by aburnott          #+#    #+#             */
/*   Updated: 2023/10/16 16:59:07 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

char	*ft_strdup(char *s, int start, int end)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = end - start;
	dup = ft_malloc(sizeof(*dup) * len + 1);
	i = 0;
	while (s[start] == ' ')
		start++;
	while (s[start] && start < end)
	{
		dup[i] = s[start];
		i++;
		start++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strdup_modif(char *s, int start, int end)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = end - start;
	dup = ft_malloc(sizeof(*dup) * len + 1);
	i = 0;
	while (s[start] && start < end)
	{
		if (s[start] == '\n')
			dup[i] = ' ';
		else
			dup[i] = s[start];
		i++;
		start++;
	}
	while (start < end)
	{
		dup[i] = ' ';
		i++;
		start++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

void	*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		error(0, "A malloc error occured, exiting the program\n", 0);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
