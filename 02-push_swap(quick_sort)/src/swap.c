/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:56:29 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/23 00:31:38 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	a_to_b(int start, int size, t_data *data)
{
	int			idx;
	int			ra_cnt;
	int			rb_cnt;
	int			pb_cnt;
	int			top;
	t_pivots	pivots;

	ra_cnt = 0;
	if (size < 3)
	{
		if (size == 1)
			return ;
		if (!is_deque_sorted(&data->a, 2))
			sa(&data->a, &data->to_print);
		return ;
	}
	idx = 0;
	rb_cnt = 0;
	pb_cnt = 0;
	pivots.min = start + size / 3;
	pivots.max = start + size / 3 * 2;
	while (idx < size)
	{
		top = deque_get_top(&data->a);
		if (top >= pivots.max)
		{
			ra(&data->a, &data->to_print);
			ra_cnt++;
		}
		else
		{
			pb(&data->a, &data->b, &data->to_print);
			pb_cnt++;
			if (top >= pivots.min)
			{
				rb(&data->b, &data->to_print);
				rb_cnt++;
			}
		}
		idx++;
	}
	idx = 0;
	while (ra_cnt - idx > 0)
	{
		rra(&data->a, &data->to_print);
		idx++;
	}
	idx = 0;
	while (rb_cnt - idx > 0)
	{
		rrb(&data->b, &data->to_print);
		idx++;
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

	if (size < 3)
	{
		if (size == 2)
		{
			if (is_deque_sorted(&data->b, 2))
				sb(&data->b, &data->to_print);
		}
		while (size--)
			pa(&data->a, &data->b, &data->to_print);
		return ;
	}
	idx = 0;
	ra_cnt = 0;
	rb_cnt = 0;
	pa_cnt = 0;
	pivots.min = start + size / 3 + size % 3;
	pivots.max = start + size / 3 * 2 + size % 3;
	while (idx < size)
	{
		top = deque_get_top(&data->b);
		if (top < pivots.min)
		{
			rb(&data->b, &data->to_print);
			rb_cnt++;
		}
		else
		{
			pa(&data->a, &data->b, &data->to_print);
			pa_cnt++;
			if (top < pivots.max)
			{
				ra(&data->a, &data->to_print);
				ra_cnt++;
			}
		}
		idx++;
	}
	a_to_b(pivots.max, pa_cnt - ra_cnt, data);
	idx = 0;
	while (ra_cnt - idx > 0)
	{
		rra(&data->a, &data->to_print);
		idx++;
	}
	idx = 0;
	while (rb_cnt - idx > 0)
	{
		rrb(&data->b, &data->to_print);
		idx++;
	}
	a_to_b(pivots.min, ra_cnt, data);
	b_to_a(start, rb_cnt, data);
}
