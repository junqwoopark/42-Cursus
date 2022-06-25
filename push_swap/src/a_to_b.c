/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:52:39 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/25 16:55:42 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	pb_smaller_than_pivot_first(t_data *data, t_instance *instance)
{
	int	idx;
	int	top;

	idx = 0;
	while (idx < instance->size)
	{
		top = deque_get_top(&data->a);
		if (top >= instance->pivots.max)
		{
			ra(data);
			instance->ra_cnt++;
		}
		else
		{
			pb(data);
			instance->pb_cnt++;
			if (top < instance->pivots.min)
			{
				rb(data);
				instance->rb_cnt++;
			}
		}
		idx++;
	}
	data->is_first = 0;
}

static void	pb_smaller_than_pivot(t_data *data, t_instance *instance)
{
	int	idx;
	int	top;

	idx = 0;
	while (idx < instance->size)
	{
		top = deque_get_top(&data->a);
		if (top >= instance->pivots.max)
		{
			ra(data);
			instance->ra_cnt++;
		}
		else
		{
			pb(data);
			instance->pb_cnt++;
			if (top >= instance->pivots.min)
			{
				rb(data);
				instance->rb_cnt++;
			}
		}
		idx++;
	}
	reverse(instance->ra_cnt, instance->rb_cnt, data);
}

void	a_to_b(int start, int size, t_data *data)
{
	t_instance	instance;

	init_instance(&instance, start, size);
	if (size <= 3)
	{
		sort_under_three(data, size);
		return ;
	}
	if (data->is_first)
		pb_smaller_than_pivot_first(data, &instance);
	else
		pb_smaller_than_pivot(data, &instance);
	a_to_b(instance.pivots.max, instance.ra_cnt, data);
	b_to_a(instance.pivots.min, instance.rb_cnt, data);
	b_to_a(start, instance.pb_cnt - instance.rb_cnt, data);
}
