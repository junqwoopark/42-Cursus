/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:09:58 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/02 14:56:09 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_info(int argc, char **argv, t_info *info)
{
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		info->number_of_times_each_philosopher_must_eat = -1;
}

void	init_forks(t_instance *instance)
{
	pthread_mutex_t	*forks;
	int				idx;

	forks = malloc(sizeof(pthread_mutex_t) * instance->info.number_of_philosophers);
	if (forks == NULL)
		exit_with_error("init_forks: forks malloc error");
	idx = 0;
	while (idx < instance->info.number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[idx], NULL) != 0)
			exit_with_error("init_forks : pthread_mutex_init() error");
	}
}

void	init_instance(int argc, char **argv, t_instance *instance)
{
	if (!(argc == 5 || argc == 6))
		exit_with_error("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
	init_info(argc, argv, &instance->info);
	init_forks(instance);
}
