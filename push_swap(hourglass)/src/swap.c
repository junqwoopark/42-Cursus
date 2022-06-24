/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:56:29 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/22 19:33:56 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	a_to_b(t_data)
{
	int	num;
	int	top;
	int	chunk;

	chunk = 0.000000053 * (p_a->size) * (p_a->size) + 0.03 * (p_a->size) + 14.5;
	num = 0;
	while (p_a->size != 0)
	{
		top = deque_get_top(p_a);
		if (top <= num)
		{
			pb(p_a, p_b, to_print);
			num++;
		}
		else if (num < top && top <= num + chunk)
		{
			pb(p_a, p_b, to_print);
			rb(p_b, to_print);
			num++;
		}
		else if (num + chunk < top)
			ra(p_a, to_print);
	}
}

void	b_to_a(t_deque *p_a, t_deque *p_b, t_deque *to_print)
{
	int	num;
	int	idx;

	num = p_b->size - 1;
	while (p_b->size != 0)
	{
		idx = deque_get_idx_to_top(p_b, num);
		if (idx <= p_b->size / 2)
		{
			while (idx--)
				rb(p_b, to_print);
			pa(p_a, p_b, to_print);
		}
		else
		{
			idx = p_b->size - idx;
			while (idx--)
				rrb(p_b, to_print);
			pa(p_a, p_b, to_print);
		}
		num--;
	}
}
