/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_under_five.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:23:22 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/25 16:44:45 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_data *data)
{
	sa(data);
}

void	sort_three(t_data *data)
{
	int	idx;
	int	num;

	num = deque_get_max(&data->a, 3);
	idx = deque_get_idx(&data->a, num);
	if (idx == 0)
		ra(data);
	else if (idx == 1)
		rra(data);
	if (!is_deque_sorted(&data->a, 3))
		sa(data);
}

void	sort_four(t_data *data)
{
	int	idx;
	int	num;

	num = 0;
	idx = deque_get_idx(&data->a, num);
	if (idx >= 2)
	{
		while (idx--)
			ra(data);
	}
	else
	{
		idx = data->a.size - idx;
		while (idx--)
			rra(data);
	}
	pb(data);
	sort_three(data);
	pa(data);
}

void	sort_five(t_data *data)
{
	int	cnt;
	int	top;

	cnt = 2;
	while (cnt)
	{
		top = deque_get_top(&data->a);
		if (top == 0 || top == 1)
		{
			pb(data);
			cnt--;
			continue ;
		}
		ra(data);
	}
	if (!is_deque_sorted(&data->a, 3))
		sort_three(data);
	pa(data);
	pa(data);
	if (!is_deque_sorted(&data->a, 2))
		sort_two(data);
}

void	sort_under_five(t_data *data)
{
	int	size;

	size = data->a.size;
	if (size == 5)
		sort_five(data);
	else if (size == 4)
		sort_four(data);
	else if (size == 3)
		sort_three(data);
	else if (size == 2)
		sort_two(data);
}
