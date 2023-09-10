/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:11:06 by aburnott          #+#    #+#             */
/*   Updated: 2023/05/08 11:06:15 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philosophers(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].meals_eaten = 0;
		rules->philo[i].last_meal = 0;
		rules->philo[i].rules = rules;
		rules->philo[i].limits = 0;
		rules->philo[i].left_fork = &rules->fork[i];
		rules->philo[i].right_fork = &rules->fork[(i + 1) % rules->nb_philo];
		i++;
	}
}

static int	allocation(t_rules *rules)
{
	int	i;

	i = 0;
	rules->philo = malloc(sizeof (t_philo) * rules->nb_philo);
	if (!rules->philo)
		return (4);
	rules->fork = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->fork)
	{
		free(rules->philo);
		return (4);
	}
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->fork[i], NULL))
			return (error_clean(rules, i, 0));
		i++;
	}
	rules->start = get_time();
	if (pthread_mutex_init(&rules->logs, NULL))
		return (error_clean(rules, i, 1));
	rules->dead = 0;
	init_philosophers(rules);
	return (init_thread(rules));
}

int	init(char **av)
{
	t_rules	rules;

	rules.nb_philo = ft_atoi(av[1]);
	rules.time_to_die = ft_atoi(av[2]);
	rules.time_to_eat = ft_atoi(av[3]);
	rules.time_to_sleep = ft_atoi(av[4]);
	rules.num_meals = 0;
	rules.count = rules.nb_philo;
	if (av[5] != 0)
		rules.num_meals = ft_atoi(av[5]);
	if (rules.time_to_die < 0 || rules.time_to_eat < 0
		|| rules.time_to_sleep < 0 || rules.nb_philo < 0
		|| rules.num_meals < 0)
		return (3);
	return (allocation(&rules));
}
