/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:53:09 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/25 16:56:02 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	pa_bigger_than_pivot(t_data *data, t_instance *instance)
{
	int	idx;
	int	top;

	idx = 0;
	while (idx < instance->size)
	{
		top = deque_get_top(&data->b);
		if (top < instance->pivots.min)
		{
			rb(data);
			instance->rb_cnt++;
		}
		else
		{
			pa(data);
			instance->pa_cnt++;
			if (top < instance->pivots.max)
			{
				ra(data);
				instance->ra_cnt++;
			}
		}
		idx++;
	}
}

void	b_to_a(int start, int size, t_data *data)
{
	int			idx;
	t_instance	instance;

	init_instance(&instance, start, size);
	if (size <= 3)
	{
		idx = size;
		while (idx--)
			pa(data);
		sort_under_three(data, size);
		return ;
	}
	pa_bigger_than_pivot(data, &instance);
	a_to_b(instance.pivots.max, instance.pa_cnt - instance.ra_cnt, data);
	reverse(instance.ra_cnt, instance.rb_cnt, data);
	a_to_b(instance.pivots.min, instance.ra_cnt, data);
	b_to_a(start, instance.rb_cnt, data);
}
