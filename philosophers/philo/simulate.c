/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:24:46 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/20 19:49:31 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*solo_routine(void *arg)
{
	t_shared	*shared;
	t_philo		*philo;

	philo = (t_philo *) arg;
	shared = philo->shared;
	pthread_mutex_lock(&shared->forks[0]);
	print_atomic(philo, "has taken a fork\n");
	ft_msleep(shared->time.die);
	pthread_mutex_unlock(&shared->forks[0]);
	print_atomic(philo, "is died\n");
	return (NULL);
}

void	simulate_solo(t_instance *instance)
{
	t_philo		*philo;
	t_shared	*shared;

	philo = &instance->philos[0];
	shared = &instance->shared;
	shared->time.start = get_ms_of_day();
	if (shared->observer.is_error)
		return ;
	if (pthread_create(&philo->thread, NULL, solo_routine, (void *) philo))
	{
		shared->observer.is_error = 1;
		return ;
	}
	pthread_join(philo->thread, NULL);
	return ;
}

static void	create_threads(t_instance *instance)
{
	int			idx;
	t_philo		*philos;
	t_shared	*shared;

	idx = 0;
	shared = &instance->shared;
	philos = instance->philos;
	while (idx < shared->number.philosophers)
	{
		philos[idx].last_meal = instance->shared.time.start;
		if (pthread_create(&philos[idx].thread, NULL, routine, &philos[idx]))
		{
			pthread_mutex_lock(shared->event);
			shared->observer.is_error = 1;
			pthread_mutex_unlock(shared->event);
		}
		idx++;
	}
}

static void	join_threads(t_instance *instance)
{
	int			idx;
	t_philo		*philos;
	t_shared	*shared;

	idx = 0;
	shared = &instance->shared;
	philos = instance->philos;
	while (idx < shared->number.philosophers)
	{
		pthread_join(philos[idx].thread, NULL);
		idx++;
	}
}

void	simulate_philosophers(t_instance *instance)
{
	t_philo		*philos;
	t_shared	*shared;

	shared = &instance->shared;
	philos = instance->philos;
	shared->time.start = get_ms_of_day();
	if (shared->observer.is_error)
		return ;
	create_threads(instance);
	observing(shared, philos);
	join_threads(instance);
}
