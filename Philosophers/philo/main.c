/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:04:49 by aburnott          #+#    #+#             */
/*   Updated: 2023/04/29 10:14:47 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	main(int ac, char **av)
{
	if (ac >= 5 && ac <= 6)
		return (print_error(init(av)));
	else
	{
		if (ac < 5)
			return (print_error(1));
		else
			return (print_error(2));
	}
	return (0);
}
