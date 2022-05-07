/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:27:31 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/22 12:48:00 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_deque *stack_a)
{
	int	data;

	data = deque_pop_right(stack_a);
	deque_push_left(stack_a, data);
}

void	rb(t_deque *stack_b)
{
	int	data;

	data = deque_pop_right(stack_b);
	deque_push_left(stack_b, data);
}

void	rr(t_deque *stack_a, t_deque *stack_b)
{
	ra(stack_a);
	rb(stack_b);
}
