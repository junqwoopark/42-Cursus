/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 00:33:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/09 23:01:20 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->tid % 2)
	{
		pthread_mutex_lock(philo->lfork);
		print_event(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->rfork);
		print_event(philo, "has taken two forks\n");
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		print_event(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->lfork);
		print_event(philo, "has taken two forks\n");
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->tid % 2)
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
	}
	else
	{
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
	}
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	philo->last_meal = get_us_of_day();
	philo->meal_cnt += 1;
	print_event(philo, "is eating\n");
	usleep(philo->rule->time.eat);
	release_forks(philo);
}

void	sleeping(t_philo *philo)
{
	print_event(philo, "is sleeping\n");
	usleep(philo->rule->time.sleep);
}

void	thinking(t_philo *philo)
{
	print_event(philo, "is thinking\n");
	usleep(100);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->rule->is_ready == 0)
	{
	}
	philo->last_meal = get_us_of_day();
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}
