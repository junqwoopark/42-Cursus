/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:27:31 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/09 15:50:31 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_deque *stack_a, t_deque *to_print)
{
	int	data;

	data = deque_pop_left(stack_a);
	deque_push_right(stack_a, data);
	deque_push_right(to_print, RRA);
}

void	rrb(t_deque *stack_b, t_deque *to_print)
{
	int	data;

	data = deque_pop_left(stack_b);
	deque_push_right(stack_b, data);
	deque_push_right(to_print, RRB);
}

void	rrr(t_deque *stack_a, t_deque *stack_b, t_deque *to_print)
{
	rra(stack_a, to_print);
	rrb(stack_b, to_print);
}
