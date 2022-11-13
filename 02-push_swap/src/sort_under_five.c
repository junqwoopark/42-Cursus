/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_under_five.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:23:22 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/30 16:42:14 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_two(t_data *data)
{
	sa(data);
}

static void	sort_three(t_data *data)
{
	int	idx;
	int	num;

	num = deque_get_max(&data->a, 3);
	idx = deque_find_idx(&data->a, num);
	if (idx == 0)
		ra(data);
	else if (idx == 1)
		rra(data);
	if (!is_deque_sorted(&data->a, 3))
		sa(data);
}

static void	sort_four(t_data *data)
{
	int	idx;
	int	num;

	num = 0;
	idx = deque_find_idx(&data->a, num);
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

static void	sort_five(t_data *data)
{
	int	cnt;
	int	back;

	cnt = 2;
	while (cnt)
	{
		back = deque_get_back(&data->a);
		if (back == 0 || back == 1)
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

void	sort_under_five(t_data *data, int size)
{
	if (is_deque_sorted(&data->a, size))
		return ;
	if (size == 2)
		sort_two(data);
	else if (size == 3)
	{
		if (data->a.size == size)
			sort_three(data);
		else
			sort_three_while_recursive(data);
	}
	else if (size == 4)
		sort_four(data);
	else if (size == 5)
		sort_five(data);
}
