/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:09:58 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/18 15:23:35 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_argv(int argc, char **argv, t_shared *shared)
{
	shared->observer.nbr_of_full = 0;
	shared->observer.is_end = 0;
	shared->observer.is_error = 0;
	if (!(argc == 5 || argc == 6))
	{
		shared->observer.is_error = 1;
		return ;
	}
	shared->time.die = ft_atoi(argv[2]);
	shared->time.eat = ft_atoi(argv[3]);
	shared->time.sleep = ft_atoi(argv[4]);
	shared->time.start = get_ms_of_day();
	shared->number.philosophers = ft_atoi(argv[1]);
	if (argc == 6)
		shared->number.must_eat = ft_atoi(argv[5]);
	else
		shared->number.must_eat = -2;
	if (shared->time.die == -1 || shared->time.eat == -1
		|| shared->time.sleep == -1 || shared->number.philosophers == -1
		|| shared->number.must_eat == -1)
		shared->observer.is_error = 1;
	return ;
}

static void	init_forks(t_shared *shared)
{
	int	idx;

	if (shared->observer.is_error)
		return ;
	shared->forks = malloc(sizeof(pthread_mutex_t)
			* shared->number.philosophers);
	if (shared->forks == NULL)
	{
		shared->observer.is_error = 1;
		return ;
	}
	idx = 0;
	while (idx < shared->number.philosophers)
	{
		if (pthread_mutex_init(&(shared->forks[idx]), NULL) != 0)
			shared->observer.is_error = 1;
		idx++;
	}
}

static void	init_mutex(t_shared *shared)
{
	shared->print = malloc(sizeof(pthread_mutex_t));
	if (shared->print == NULL)
	{
		shared->observer.is_error = 1;
		return ;
	}
	if (pthread_mutex_init(shared->print, NULL) != 0)
		shared->observer.is_error = 1;
	shared->event = malloc(sizeof(pthread_mutex_t));
	if (shared->event == NULL)
	{
		shared->observer.is_error = 1;
		return ;
	}
	if (pthread_mutex_init(shared->event, NULL) != 0)
		shared->observer.is_error = 1;
}

static void	init_philos(t_instance *instance)
{
	int			idx;
	t_shared	*shared;
	t_philo		*philos;

	shared = &instance->shared;
	if (shared->observer.is_error)
		return ;
	instance->philos = malloc(sizeof(t_philo) * shared->number.philosophers);
	philos = instance->philos;
	if (philos == NULL)
		shared->observer.is_error = 1;
	idx = 0;
	while (idx < shared->number.philosophers)
	{
		philos[idx].tid = idx + 1;
		philos[idx].meal_cnt = 0;
		philos[idx].lfork = &(shared->forks[idx]);
		philos[idx].rfork = &(shared->forks[
				(idx + shared->number.philosophers - 1)
				% shared->number.philosophers]);
		philos[idx].shared = shared;
		philos[idx].last_meal = shared->time.start;
		idx++;
	}
	instance->shared.philos = instance->philos;
}

void	init_instance(int argc, char **argv, t_instance *instance)
{
	if (!(argc == 5 || argc == 6))
		instance->shared.observer.is_error = 1;
	init_argv(argc, argv, &instance->shared);
	init_forks(&instance->shared);
	init_mutex(&instance->shared);
	init_philos(instance);
}
