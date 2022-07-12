/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:23:28 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/30 16:54:21 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_deque(int argc, char **argv, t_data *data)
{
	int	idx;
	int	val;

	deque_init(&data->a);
	deque_init(&data->b);
	deque_init(&data->result);
	idx = 1;
	while (idx < argc)
	{
		val = ft_atoi(argv[idx]);
		if (deque_find_node(&data->a, val))
		{
			free_deques(data);
			exit_with_err("Error\n");
		}
		deque_push_front(&data->a, val);
		idx++;
	}
}

void	init_data(int argc, char **argv, t_data *data)
{
	data->is_first = 1;
	init_deque(argc, argv, data);
	label_data(argv, data);
}

void	init_instance(t_instance *instance, int start, int size)
{
	ft_bzero(instance, sizeof(t_instance));
	instance->size = size;
	instance->pivots.min = start + size / 3;
	instance->pivots.max = start + size / 3 * 2;
}
