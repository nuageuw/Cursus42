/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:53:13 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/25 13:53:16 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write (1, &str[i], 1);
	write (1, "\n", 1);
}

float	next_atof(char *arr, int *check, float scale, int afterdot)
{
	float	val;

	val = 0;
	while (*arr)
	{
		if ((*arr >= '0' && *arr <= '9') || *arr == '.')
		{
			if (afterdot)
			{
				scale = scale / 10;
				val = val + (*arr - '0') * scale;
			}
			else
			{
				if (*arr == '.')
					afterdot++;
				else
					val = val * 10.0 + (*arr - '0');
			}
			arr++;
		}
		else
			return (*check = 1);
	}
	return (val);
}

float	ft_atof(char *arr, int *check)
{
	float	val;
	int		afterdot;
	int		neg;

	val = 0;
	afterdot = 0;
	neg = 0;
	if (*arr == '-' || *arr == '+')
	{
		if (*arr == '-')
			neg = 1;
		arr++;
	}
	if (!*arr)
		*check = 1;
	val = next_atof(arr, check, 1, 0);
	if (neg)
		return (-val);
	else
		return (val);
}
