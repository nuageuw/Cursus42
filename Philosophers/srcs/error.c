/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:07:32 by aburnott          #+#    #+#             */
/*   Updated: 2023/04/29 20:08:45 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	error_2(int code)
{
	if (code == 4)
		ft_putstr_fd("Malloc allocation error.\n", 2);
	if (code == 5)
		ft_putstr_fd("Mutex initialization error.\n", 2);
	if (code == 6)
		ft_putstr_fd("Thread initialization error.\n", 2);
}

int	print_error(int code)
{
	if (code == 1)
	{
		ft_putstr_fd("Not enough arguments.\nUsage: number_of_philosophers ", 2);
		ft_putstr_fd("time_to_die time_to_eat time_to_sleep ", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
	}
	else if (code == 2)
	{
		ft_putstr_fd("Too many arguments.\nUsage: number_of_philosophers ", 2);
		ft_putstr_fd("time_to_die time_to_eat time_to_sleep ", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
	}
	else if (code == 3)
		ft_putstr_fd("Error with arguments provided.\n", 2);
	else
		error_2(code);
	return (1);
}
