/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 00:33:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/18 20:30:40 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	take_forks(philo);
	print_atomic(philo, "is eating\n");
	ft_usleep(philo->shared->time.eat);
	release_forks(philo);
}

static void	sleeping(t_philo *philo)
{
	print_atomic(philo, "is sleeping\n");
	ft_usleep(philo->shared->time.sleep);
}

static void	thinking(t_philo *philo)
{
	print_atomic(philo, "is thinking\n");
	usleep(100);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->tid % 2)
		usleep(1000);
	while (1)
	{
		if (check_atomic(philo->shared, IS_END))
			return (NULL);
		eating(philo);
		if (check_atomic(philo->shared, IS_END))
			return (NULL);
		sleeping(philo);
		thinking(philo);
	}
}
