/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:27:31 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 21:34:59 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_deque *stack_a, t_deque *to_print)
{
	int	data;

	data = deque_pop_top(stack_a);
	deque_push_bottom(stack_a, data);
	deque_push_top(to_print, RA);
}

void	rb(t_deque *stack_b, t_deque *to_print)
{
	int	data;

	data = deque_pop_top(stack_b);
	deque_push_bottom(stack_b, data);
	deque_push_top(to_print, RB);
}

void	rr(t_deque *stack_a, t_deque *stack_b, t_deque *to_print)
{
	ra(stack_a, to_print);
	rb(stack_b, to_print);
}
