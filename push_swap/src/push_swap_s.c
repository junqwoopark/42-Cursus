/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:21:51 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/22 12:26:49 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_deque *stack_a)
{
	int	first_data;
	int	second_data;

	first_data = deque_pop_right(stack_a);
	second_data = deque_pop_right(stack_a);
	deque_push_right(stack_a, first_data);
	deque_push_right(stack_a, second_data);
}

void	sb(t_deque *stack_b)
{
	int	first_data;
	int	second_data;

	first_data = deque_pop_right(stack_b);
	second_data = deque_pop_right(stack_b);
	deque_push_right(stack_b, first_data);
	deque_push_right(stack_b, second_data);
}

void	ss(t_deque *stack_a, t_deque *stack_b)
{
	sa(stack_a);
	sb(stack_b);
}
