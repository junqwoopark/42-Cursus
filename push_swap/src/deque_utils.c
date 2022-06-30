/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:35:25 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:14:07 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deque_init(t_deque *p_deque)
{
	p_deque->size = 0;
	p_deque->front = NULL;
	p_deque->back = NULL;
}

int	is_deque_empty(t_deque *p_deque)
{
	if (deque_get_size(p_deque) == 0)
		return (TRUE);
	return (FALSE);
}

int	is_deque_sorted(t_deque *deque, int size)
{
	int			x;
	int			idx;
	t_node		*node;

	x = deque->back->data;
	node = deque->back->prev;
	idx = 0;
	while (node && idx < size - 1)
	{
		if (node->data > x)
			x = node->data;
		else
			return (FALSE);
		node = node->prev;
		idx++;
	}
	return (TRUE);
}

int	is_deque_sorted_reversed(t_deque *deque, int size)
{
	int			x;
	int			idx;
	t_node		*node;

	x = deque->back->data;
	node = deque->back->prev;
	idx = 0;
	while (node && idx < size - 1)
	{
		if (node->data < x)
			x = node->data;
		else
			return (FALSE);
		node = node->prev;
		idx++;
	}
	return (TRUE);
}
