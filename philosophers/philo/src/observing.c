/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:39:28 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/18 15:30:26 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_is_dead(t_shared *shared, t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < shared->number.philosophers)
	{
		if (check_mutex(shared, philos, TIME_PASSED, idx))
		{
			print_mutex(&philos[idx], "is died\n");
			pthread_mutex_lock(shared->event);
			shared->observer.is_end = 1;
			pthread_mutex_unlock(shared->event);
			return (1);
		}
		idx++;
	}
	return (0);
}

void	observing(t_shared *shared, t_philo *philos)
{
	if (shared->observer.is_error)
	{
		pthread_mutex_lock(shared->event);
		shared->observer.is_end = 1;
		pthread_mutex_unlock(shared->event);
	}
	while (1)
	{
		if (check_mutex(shared, philos, IS_END, 0))
			return ;
		if (check_is_dead(shared, philos)
			|| check_mutex(shared, philos, IS_FULL, 0))
			break ;
	}
	return ;
}
