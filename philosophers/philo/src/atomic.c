/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:21:24 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/18 20:51:56 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	print_atomic(t_philo *philo, char *print)
{
	pthread_mutex_lock(philo->shared->print);
	if (!strcmp(print, "is died\n"))
	{
		printf("%ld %d %s", get_ms_of_passed_time(philo->shared->time.start),
			philo->tid, print);
		pthread_mutex_unlock(philo->shared->print);
		return ;
	}
	pthread_mutex_lock(philo->shared->event);
	if (!philo->shared->observer.is_end)
	{
		printf("%ld %d %s", get_ms_of_passed_time(philo->shared->time.start),
			philo->tid, print);
		pthread_mutex_unlock(philo->shared->event);
	}
	else
		pthread_mutex_unlock(philo->shared->event);
	pthread_mutex_unlock(philo->shared->print);
}

int	check_atomic(t_shared *shared, int to_check)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(shared->event);
	if (to_check == IS_END)
	{
		if (shared->observer.is_end)
			ret = 1;
	}
	else if (to_check == IS_FULL)
	{
		if (shared->observer.nbr_of_full == shared->number.philosophers)
		{
			shared->observer.is_end = 1;
			ret = 1;
		}
	}
	pthread_mutex_unlock(shared->event);
	return (ret);
}
