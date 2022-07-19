/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:21:24 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/19 16:10:55 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_atomic(t_philo *philo, char *print, int to_print)
{
	pthread_mutex_lock(philo->shared->print);
	if (to_print == DIED)
	{
		printf("%ld\t%d\t%s", get_ms_of_passed_time(philo->shared->time.start),
			philo->tid, print);
		pthread_mutex_unlock(philo->shared->print);
		return ;
	}
	pthread_mutex_lock(philo->shared->event);
	if (!philo->shared->observer.is_end)
	{
		printf("%ld\t%d\t%s", get_ms_of_passed_time(philo->shared->time.start),
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
		if (shared->observer.is_end || shared->observer.is_error)
			ret = 1;
	}
	else if (to_check == IS_FULL)
	{
		if (shared->number.must_eat == 0
			|| shared->observer.nbr_of_full == shared->number.philosophers)
		{
			shared->observer.is_end = 1;
			ret = 1;
		}
	}
	pthread_mutex_unlock(shared->event);
	return (ret);
}
