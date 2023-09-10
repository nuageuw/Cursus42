/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:12:02 by aburnott          #+#    #+#             */
/*   Updated: 2023/05/04 14:54:01 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <stdatomic.h>

typedef struct s_philo	t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				count;
	atomic_int		dead;
	long long int	start;
	pthread_mutex_t	logs;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}		t_rules;

typedef struct s_philo
{
	int				id;
	atomic_int		meals_eaten;
	atomic_int		limits;
	atomic_llong	last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}				t_philo;

void		ft_putstr_fd(char *str, int fd);
int			print_error(int code);
int			ft_atoi(const char *str);
int			init(char **av);
long long	get_time(void);
void		*routine(void *philo_void);
int			init_thread(t_rules *rules);
void		check_dead(t_rules *rules, t_philo *philo);
void		ft_usleep(int time, t_rules *rules);
void		destroy(t_rules *rules, t_philo *philos);
int			error_clean(t_rules *rules, int i, int type);

#endif
