/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:56:58 by aburnott          #+#    #+#             */
/*   Updated: 2023/05/09 10:52:37 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy(t_rules *rules, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->fork[i]));
	pthread_mutex_destroy(&(rules->logs));
}

int	init_thread(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = rules->philo;
	while (i < rules->nb_philo)
	{
		philo[i].last_meal = get_time();
		if (pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]))
		{
			destroy(rules, philo);
			free(rules->fork);
			free(rules->philo);
			return (6);
		}
		i++;
	}
	check_dead(rules, rules->philo);
	destroy(rules, philo);
	free(rules->fork);
	free(rules->philo);
	return (0);
}

int	error_clean(t_rules *rules, int i, int type)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&(rules->fork[i]));
		i--;
	}
	if (type)
		pthread_mutex_destroy(&(rules->logs));
	free(rules->fork);
	free(rules->philo);
	return (5);
}
