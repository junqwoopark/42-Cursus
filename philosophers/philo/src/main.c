/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:33:37 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/16 21:36:26 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulate_philosophers(t_instance *instance)
{
	int	idx;
	t_philo		*philos;
	t_shared	*shared;

	shared = &instance->shared;
	philos = instance->philos;
	if (shared->observer.is_error)
		return ;
	if (shared->number.philosophers == 1)
	{
		print_mutex(&philos[0], "has taken a fork\n");
		ft_usleep(shared->time.die);
		print_mutex(&philos[0], "is dead\n");
		return ;
	}
	idx = 0;
	while (idx < shared->number.philosophers)
	{
		if (pthread_create(&philos[idx].thread, NULL, routine, &philos[idx]))
			shared->observer.is_error = 1;
		idx++;
	}
	observing(shared, philos);
	idx = 0;
	while (idx < shared->number.philosophers)
	{
		pthread_join(philos[idx].thread, NULL);
		idx++;
	}
}

int	main(int argc, char **argv)
{
	t_instance instance;

	init_instance(argc, argv, &instance);
	simulate_philosophers(&instance);
	if (instance.shared.observer.is_error)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
