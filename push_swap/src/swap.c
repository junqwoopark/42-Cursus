/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:56:29 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/24 19:54:40 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse(int ra_cnt, int rb_cnt, t_data *data)
{
	while (ra_cnt && rb_cnt)
	{
		rrr(data);
		ra_cnt--;
		rb_cnt--;
	}
	while (ra_cnt)
	{
		rra(data);
		ra_cnt--;
	}
	while (rb_cnt)
	{
		rrb(data);
		rb_cnt--;
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
			{
				pb(data);
				sa(data);
				pa(data);
			}
			if (min_idx == 1)
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
			if (min_idx == 2)
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
		}
	}
}

void	a_to_b(int start, int size, t_data *data)
{
	int			idx;
	int			ra_cnt;
	int			rb_cnt;
	int			pb_cnt;
	int			top;
	t_pivots	pivots;

	ra_cnt = 0;
	if (size <= 3)
	{
		sort_under_three(data, size);
		return ;
	}
	if (is_deque_sorted(&data->a, size))
		return ;
	idx = 0;
	rb_cnt = 0;
	pb_cnt = 0;
	pivots.min = start + size / 3;
	pivots.max = start + size / 3 * 2;
	if (data->is_first)
	{
		while (idx < size)
		{
			top = deque_get_top(&data->a);
			if (top >= pivots.max)
			{
				ra(data);
				ra_cnt++;
			}
			else
			{
				pb(data);
				pb_cnt++;
				if (top < pivots.min)
				{
					rb(data);
					rb_cnt++;
				}
			}
			idx++;
		}
		data->is_first = 0;
	}
	else
	{
		while (idx < size)
		{
			top = deque_get_top(&data->a);
			if (top >= pivots.max)
			{
				ra(data);
				ra_cnt++;
			}
			else
			{
				pb(data);
				pb_cnt++;
				if (top >= pivots.min)
				{
					rb(data);
					rb_cnt++;
				}
			}
			idx++;
		}
		reverse(ra_cnt, rb_cnt, data);
	}
	a_to_b(pivots.max, ra_cnt, data);
	b_to_a(pivots.min, rb_cnt, data);
	b_to_a(start, pb_cnt - rb_cnt, data);
}

void	b_to_a(int start, int size, t_data *data)
{
	int			idx;
	int			ra_cnt;
	int			rb_cnt;
	int			pa_cnt;
	int			top;
	t_pivots	pivots;

	if (size <= 3)
	{
		idx = size;
		while (idx--)
			pa(data);
		sort_under_three(data, size);
		return ;
	}
	idx = 0;
	ra_cnt = 0;
	rb_cnt = 0;
	pa_cnt = 0;
	pivots.min = start + size / 3;
	pivots.max = start + size / 3 * 2;
	while (idx < size)
	{
		top = deque_get_top(&data->b);
		if (top < pivots.min)
		{
			rb(data);
			rb_cnt++;
		}
		else
		{
			pa(data);
			pa_cnt++;
			if (top < pivots.max)
			{
				ra(data);
				ra_cnt++;
			}
		}
		idx++;
	}
	a_to_b(pivots.max, pa_cnt - ra_cnt, data);
	reverse(ra_cnt, rb_cnt, data);
	a_to_b(pivots.min, ra_cnt, data);
	b_to_a(start, rb_cnt, data);
}
