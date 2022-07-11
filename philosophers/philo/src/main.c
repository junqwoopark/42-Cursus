/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:33:37 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/09 22:32:42 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_with_error(char *err)
{
	while (*err)
	{
		write(2, err, 1);
		err++;
	}
	exit(1);
}

void	simulate_philosophers(t_instance *instance)
{
	instance->shared.rule.is_ready = 1;
	pthread_join(*instance->monitor, NULL);
}

void	check_leaks(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_instance	instance;

	init_instance(argc, argv, &instance);
	simulate_philosophers(&instance);
}
