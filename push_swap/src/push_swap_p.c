/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:15:53 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/09 15:49:49 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_deque *stack_a, t_deque *stack_b, t_deque *to_print)
{
	int	data;

	data = deque_pop_right(stack_b);
	deque_push_right(stack_a, data);
	deque_push_right(to_print, PA);
}

void	pb(t_deque *stack_a, t_deque *stack_b, t_deque *to_print)
{
	int	data;

	data = deque_pop_right(stack_a);
	deque_push_right(stack_b, data);
	deque_push_right(to_print, PB);
}
