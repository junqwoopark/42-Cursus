/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:09:58 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/16 21:57:58 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_argv(int argc, char **argv, t_shared *shared)
{
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
	if (shared->time.die == -1 ||
		shared->time.eat == -1 ||
		shared->time.sleep == -1 ||
		shared->number.philosophers == -1 ||
		shared->number.must_eat == -1)
		shared->observer.is_error = 1;
	return;
}

void	init_number(int argc, char **argv, t_number *number)
{
	number->philosophers = ft_atoi(argv[1]);
	if (argc == 6)
		number->must_eat = ft_atoi(argv[5]);
	else
		number->must_eat = -1;
}

void	init_observer(t_observer *observer)
{
	observer->nbr_of_full = 0;
	observer->is_end = 0;
	observer->is_error = 0;
}

void	init_forks(t_shared *shared)
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

void	init_mutex(t_shared *shared)
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

void	init_shared(int argc, char **argv, t_shared *shared)
{

	init_observer(&shared->observer);
	init_argv(argc, argv, shared);
	init_forks(shared);
	init_mutex(shared);
}

void	init_philos(t_instance *instance)
{
	int	idx;

	if (instance->shared.observer.is_error)
		return ;
	instance->philos = malloc(sizeof(t_philo) * instance->shared.number.philosophers);
	if (instance->philos == NULL)
		instance->shared.observer.is_error = 1;
	idx = 0;
	while (idx < instance->shared.number.philosophers)
	{
		instance->philos[idx].tid = idx + 1;
		instance->philos[idx].meal_cnt = 0;
		instance->philos[idx].lfork = &(instance->shared.forks[idx]);
		instance->philos[idx].rfork = &(instance->shared.forks[(idx + instance->shared.number.philosophers - 1)
			% instance->shared.number.philosophers]);
		instance->philos[idx].shared = &instance->shared;
		instance->philos[idx].last_meal = instance->shared.time.start;
		idx++;
	}
	instance->shared.philos = instance->philos;
}

void	init_instance(int argc, char **argv, t_instance *instance)
{
	if (!(argc == 5 || argc == 6))
		instance->shared.observer.is_error = 1;
	init_shared(argc, argv, &instance->shared);
	init_philos(instance);
}
