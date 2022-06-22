/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:24:34 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 21:35:33 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	deque_get_size(t_deque *p_deque)
{
	return (p_deque->size);
}

int	deque_get_bottom(t_deque *p_deque)
{
	if (is_deque_empty(p_deque))
		exit(1);
	return (p_deque->bottom->data);
}

int	deque_get_top(t_deque *p_deque)
{
	if (is_deque_empty(p_deque))
		exit(1);
	return (p_deque->top->data);
}

int	deque_get_max(t_deque *p_deque)
{
	t_node	*node;
	int		max;

	max = INT_MIN;
	node = p_deque->top;
	while (node)
	{
		if (node->data > max)
		{
			max = node->data;
		}
		node = node->under;
	}
	return (max);
}
