/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:37:31 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/18 15:43:45 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_atomic(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->rfork);
	print_atomic(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->shared->event);
	philo->last_meal = get_ms_of_day();
	pthread_mutex_unlock(philo->shared->event);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->shared->event);
	philo->meal_cnt += 1;
	if (philo->meal_cnt == philo->shared->number.must_eat)
		philo->shared->observer.nbr_of_full += 1;
	pthread_mutex_unlock(philo->shared->event);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}
