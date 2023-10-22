/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:30:41 by aburnott          #+#    #+#             */
/*   Updated: 2023/09/22 16:37:08 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi(const char *str, int type)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - 48;
	}
	if (str[i] == '\n')
		i++;
	if ((sign * res > INT_MAX || sign * res < INT_MIN) || str[i])
	{
		while (type == 2 && (str[i] == ' ' || str[i] == '\n'))
			i++;
		if (!str[i])
			return (sign * res);
		else
			return (-2);
	}
	return (sign * res);
}

void	ft_swap_double(double *x, double *y)
{
	double	tmp;

	tmp = *x;
	*x = *y + 0.5;
	*y = tmp + 0.5;
}
