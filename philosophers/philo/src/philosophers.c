/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 00:33:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/16 20:43:45 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_mutex(t_shared *shared, t_philo *philos, int to_check, int idx)
{
	pthread_mutex_lock(shared->event);
	if (to_check == IS_END)
	{
		if (shared->observer.is_end)
		{
			pthread_mutex_unlock(shared->event);
			return (1);
		}
	}
	if (to_check == IS_FULL)
	{
		if (shared->observer.nbr_of_full == shared->number.philosophers)
		{
			shared->observer.is_end = 1;
			pthread_mutex_unlock(shared->event);
			return (1);
		}
	}
	if (to_check == TIME_PASSED)
	{
		if (get_ms_of_passed_time(philos[idx].last_meal)
			> philos[idx].shared->time.die)
		{
			pthread_mutex_unlock(shared->event);
			return (1);
		}
	}
	pthread_mutex_unlock(shared->event);
	return (0);
}

void	ft_usleep(time_t wait_time)
{
	time_t	start_time;

	start_time = get_ms_of_day();
	while (get_ms_of_passed_time(start_time) <= wait_time)
	{
		usleep(1000);
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_mutex(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->rfork);
	print_mutex(philo, "has taken a fork\n");
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

void	eating(t_philo *philo)
{
	take_forks(philo);
	print_mutex(philo, "is eating\n");
	ft_usleep(philo->shared->time.eat);
	release_forks(philo);
}

void	sleeping(t_philo *philo)
{
	print_mutex(philo, "is sleeping\n");
	ft_usleep(philo->shared->time.sleep);
}

void	thinking(t_philo *philo)
{
	print_mutex(philo, "is thinking\n");
	usleep(200);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->tid % 2)
		usleep(1000);
	while (1)
	{
		if (check_mutex(philo->shared, philo->shared->philos, IS_END, 0))
			return (NULL);
		eating(philo);
		if (check_mutex(philo->shared, philo->shared->philos, IS_END, 0))
			return (NULL);
		sleeping(philo);
		thinking(philo);
	}
}
