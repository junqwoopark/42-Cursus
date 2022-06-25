/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_under_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:23:28 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/25 15:31:10 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three_min_is_top(t_data *data)
{
	pb(data);
	sa(data);
	pa(data);
}

static void	sort_three_min_is_mid(t_data *data, int max_idx)
{
	if (max_idx == 2)
		sa(data);
	else
	{
		sa(data);
		pb(data);
		sa(data);
		pa(data);
	}
}

static void	sort_three_min_is_bottom(t_data *data, int max_idx)
{
	if (max_idx == 1)
	{
		pb(data);
		pb(data);
		ra(data);
		pa(data);
		pa(data);
		rra(data);
	}
	else
	{
		pb(data);
		pb(data);
		ra(data);
		pa(data);
		pa(data);
		sa(data);
		rra(data);
	}
}

void	sort_under_three(t_data *data, int size)
{
	int	min;
	int	min_idx;
	int	max_idx;

	if (!is_deque_sorted(&data->a, size))
	{
		if (size == 2)
			sa(data);
		if (size == 3)
		{
			min = deque_get_min(&data->a, size);
			min_idx = deque_get_idx(&data->a, min);
			max_idx = deque_get_idx(&data->a, min + 2);
			if (min_idx == 0)
				sort_three_min_is_top(data);
			if (min_idx == 1)
				sort_three_min_is_mid(data, max_idx);
			if (min_idx == 2)
				sort_three_min_is_bottom(data, max_idx);
		}
	}
}
