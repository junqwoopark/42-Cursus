/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:39:28 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/20 19:41:28 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_is_died(t_shared *shared, t_philo *philos)
{
	int		idx;
	time_t	passed_time;

	idx = 0;
	while (idx < shared->number.philosophers)
	{
		pthread_mutex_lock(shared->event);
		passed_time = get_ms_of_passed_time(philos[idx].last_meal);
		if (passed_time > shared->time.die)
		{
			shared->observer.is_end = 1;
			printf("%ld\t%d\tis died\n",
				passed_time, idx + 1);
			pthread_mutex_unlock(shared->event);
			return (1);
		}
		pthread_mutex_unlock(shared->event);
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
		if (check_atomic(shared, IS_END))
			return ;
		if (check_is_died(shared, philos)
			|| check_atomic(shared, IS_FULL))
			break ;
		ft_msleep(1);
	}
	return ;
}
