/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:57:41 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/11 15:41:36 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

int	ft_atoi(const char *str, int *check)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - 48;
	if (sign * res > INT_MAX || sign * res < INT_MIN
		|| str[i] || i == 0)
		*check = 1;
	return (sign * res);
}

void	ft_free(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*value;
	t_node	*tmp;

	value = stack_a->head;
	while (value)
	{
		tmp = value;
		value = value->next;
		free(tmp);
	}
	free(stack_a);
	free(stack_b);
}

void	ft_free_arr(char **arr)
{
	int	index;

	if (!arr)
		return ;
	index = 0;
	while (arr[index])
		free(arr[index++]);
	free(arr);
}
