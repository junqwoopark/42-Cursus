/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:21:51 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 21:34:51 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_deque *stack_a, t_deque *to_print)
{
	int	first_data;
	int	second_data;

	first_data = deque_pop_top(stack_a);
	second_data = deque_pop_top(stack_a);
	deque_push_top(stack_a, first_data);
	deque_push_top(stack_a, second_data);
	deque_push_top(to_print, SA);
}

void	sb(t_deque *stack_b, t_deque *to_print)
{
	int	first_data;
	int	second_data;

	first_data = deque_pop_top(stack_b);
	second_data = deque_pop_top(stack_b);
	deque_push_top(stack_b, first_data);
	deque_push_top(stack_b, second_data);
	deque_push_top(to_print, SB);
}

void	ss(t_deque *stack_a, t_deque *stack_b, t_deque *to_print)
{
	sa(stack_a, to_print);
	sb(stack_b, to_print);
}
