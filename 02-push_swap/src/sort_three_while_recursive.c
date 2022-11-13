/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_while_recursive.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:41:16 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/30 16:41:21 by junkpark         ###   ########.fr       */
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

void	sort_three_while_recursive(t_data *data)
{
	int	min;
	int	min_idx;
	int	max_idx;

	min = deque_get_min(&data->a, 3);
	min_idx = deque_find_idx(&data->a, min);
	max_idx = deque_find_idx(&data->a, min + 2);
	if (min_idx == 0)
		sort_three_min_is_top(data);
	if (min_idx == 1)
		sort_three_min_is_mid(data, max_idx);
	if (min_idx == 2)
		sort_three_min_is_bottom(data, max_idx);
}
