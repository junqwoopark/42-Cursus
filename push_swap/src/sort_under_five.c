/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_under_five.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:23:22 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/24 15:11:22 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_deque *a, t_deque *to_print)
{
	sa(a, to_print);
}

void	sort_three(t_deque *a, t_deque *to_print)
{
	int	idx;
	int	num;

	num = deque_get_max(a);
	idx = deque_get_idx_to_top(a, num);
	if (idx == 0)
		ra(a, to_print);
	else if (idx == 1)
		rra(a, to_print);
	if (!is_deque_sorted(a))
		sa(a, to_print);
}

void	sort_four(t_deque *a, t_deque *b, t_deque *to_print)
{
	int	idx;
	int	num;

	num = 0;
	idx = deque_get_idx_to_top(a, num);
	if (idx >= a->size / 2)
	{
		while (idx--)
			ra(a, to_print);
	}
	else
	{
		idx = a->size - idx;
		while (idx--)
			rra(a, to_print);
	}
	pb(a, b, to_print);
	sort_three(a, to_print);
	pa(a, b, to_print);
}

void	sort_five(t_deque *a, t_deque *b, t_deque *to_print)
{
	int	cnt;

	cnt = 2;
	while (cnt)
	{
		if (deque_get_right(a) == 0 || deque_get_right(a) == 1)
		{
			pb(a, b, to_print);
			cnt--;
			continue ;
		}
		ra(a, to_print);
	}
	sort_three(a, to_print);
	if (is_deque_sorted(b))
		sb(b, to_print);
	pa(a, b, to_print);
	pa(a, b, to_print);
}


void	sort_under_five(t_deque *a, t_deque *b, t_deque *to_print)
{
	if (a->size == 5)
		sort_five(a, b, to_print);
	else if (a->size == 4)
		sort_four(a, b, to_print);
	else if (a->size == 3)
		sort_three(a, to_print);
	else if (a->size == 2)
		sort_two(a, to_print);
}
