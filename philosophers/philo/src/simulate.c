/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:24:46 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/18 22:23:36 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	simulate_solo(t_instance *instance)
{
	t_philo		*philos;
	t_shared	*shared;

	shared = &instance->shared;
	philos = instance->philos;
	pthread_mutex_lock(&shared->forks[0]);
	print_atomic(&philos[0], "has taken a fork\n", EVENT);
	ft_msleep(shared->time.die);
	pthread_mutex_unlock(&shared->forks[0]);
	print_atomic(&philos[0], "is dead\n", EVENT);
	return ;
}

void	simulate_philosophers(t_instance *instance)
{
	int			idx;
	t_philo		*philos;
	t_shared	*shared;

	shared = &instance->shared;
	philos = instance->philos;
	if (shared->observer.is_error)
		return ;
	if (shared->number.philosophers == 1)
		return (simulate_solo(instance));
	idx = 0;
	instance->shared.time.start = get_ms_of_day();
	while (idx < shared->number.philosophers)
	{
		philos[idx].last_meal = instance->shared.time.start;
		if (pthread_create(&philos[idx].thread, NULL, routine, &philos[idx]))
			shared->observer.is_error = 1;
		idx++;
	}
	observing(shared, philos);
	idx = 0;
	while (idx < shared->number.philosophers)
	{
		pthread_join(philos[idx].thread, NULL);
		idx++;
	}
}
