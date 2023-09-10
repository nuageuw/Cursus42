/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:57:04 by aburnott          #+#    #+#             */
/*   Updated: 2023/05/09 13:48:42 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	display_message(t_philo *philo, char *message)
{
	if (!philo->rules->dead)
	{
		pthread_mutex_lock(&philo->rules->logs);
		printf("%lld %d %s\n", get_time() - philo->rules->start,
			philo->id, message);
		pthread_mutex_unlock(&philo->rules->logs);
	}
}

static int	eat_part(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display_message(philo, "has taken a fork");
	if (philo->rules->nb_philo == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	display_message(philo, "has taken a fork");
	display_message(philo, "is eating");
	philo->last_meal = get_time();
	ft_usleep(philo->rules->time_to_eat, philo->rules);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if ((!philo->id % 2))
		ft_usleep((philo->rules->time_to_eat / 2), philo->rules);
	while (!philo->rules->dead)
	{
		if (philo->rules->num_meals != 0
			&& philo->meals_eaten >= philo->rules->num_meals)
				philo->limits = 1;
		if (!eat_part(philo))
			break ;
		display_message(philo, "is sleeping");
		ft_usleep(philo->rules->time_to_sleep, philo->rules);
		display_message(philo, "is thinking");
	}
	return (NULL);
}

void	check_dead(t_rules *rules, t_philo *philo)
{
	int	i;

	while (!rules->dead)
	{
		if (!rules->count)
			rules->dead = 1;
		i = 0;
		while (i < rules->nb_philo)
		{
			if (philo->limits)
				rules->count--;
			if (!rules->count)
				break ;
			if ((get_time() - philo[i].last_meal) > rules->time_to_die)
			{
				display_message(philo, "died");
				philo->rules->dead = 1;
				return ;
			}
			i++;
		}
	}
}
