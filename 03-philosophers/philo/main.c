/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:33:37 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/20 19:55:23 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_instance	instance;

	init_instance(argc, argv, &instance);
	if (!instance.shared.observer.is_error
		&& instance.shared.number.must_eat == 0)
		return (0);
	else if (instance.shared.number.philosophers == 1)
		simulate_solo(&instance);
	else
		simulate_philosophers(&instance);
	if (instance.shared.observer.is_error)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
