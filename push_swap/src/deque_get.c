/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:24:34 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/24 14:39:06 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	deque_get_size(t_deque *p_deque)
{
	return (p_deque->size);
}

int	deque_get_left(t_deque *p_deque)
{
	if (is_deque_empty(p_deque))
		exit(1);
	return (p_deque->left->data);
}

int	deque_get_right(t_deque *p_deque)
{
	if (is_deque_empty(p_deque))
		exit(1);
	return (p_deque->right->data);
}

int	deque_get_max(t_deque *p_deque)
{
	t_node	*node;
	int		max;

	max = INT_MIN;
	node = p_deque->right;
	while (node)
	{
		if (node->data > max)
		{
			max = node->data;
		}
		node = node->prev;
	}
	return (max);
}
