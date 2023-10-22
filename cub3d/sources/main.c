/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:36:12 by aburnott          #+#    #+#             */
/*   Updated: 2023/09/13 13:17:30 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 2)
		error(0, "Invalid number of arguments\n", 0);
	while (av[1][i])
		i++;
	if (av[1][i - 1] != 'b' || av[1][i - 2] != 'u'
		|| av[1][i - 3] != 'c' || av[1][i - 4] != '.')
		error(0, "Invalid file extension\n", 0);
	init_struc(av[1]);
	return (0);
}
