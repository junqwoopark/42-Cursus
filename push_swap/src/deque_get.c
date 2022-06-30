/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:24:34 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:14:07 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	deque_get_size(t_deque *p_deque)
{
	return (p_deque->size);
}

int	deque_get_front(t_deque *p_deque)
{
	if (is_deque_empty(p_deque))
		exit(1);
	return (p_deque->front->data);
}

int	deque_get_back(t_deque *p_deque)
{
	if (is_deque_empty(p_deque))
		exit(1);
	return (p_deque->back->data);
}

int	deque_get_max(t_deque *p_deque, int size)
{
	t_node	*node;
	int		max;
	int		idx;

	idx = 0;
	max = INT_MIN;
	node = p_deque->back;
	while (node && idx < size)
	{
		if (node->data > max)
		{
			max = node->data;
		}
		node = node->prev;
		idx++;
	}
	return (max);
}

int	deque_get_min(t_deque *p_deque, int size)
{
	t_node	*node;
	int		min;
	int		idx;

	idx = 0;
	min = INT_MAX;
	node = p_deque->back;
	while (node && idx < size)
	{
		if (node->data < min)
		{
			min = node->data;
		}
		node = node->prev;
		idx++;
	}
	return (min);
}
