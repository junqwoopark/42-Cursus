/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:27:31 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/22 12:33:06 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_deque *stack_a)
{
	int	data;

	data = deque_pop_left(stack_a);
	deque_push_right(stack_a, data);
}

void	rrb(t_deque *stack_b)
{
	int	data;

	data = deque_pop_left(stack_b);
	deque_push_right(stack_b, data);
}

void	rrr(t_deque *stack_a, t_deque *stack_b)
{
	rra(stack_a);
	rrb(stack_b);
}
