/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:35:25 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/24 14:57:56 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deque_init(t_deque *p_deque)
{
	p_deque->size = 0;
	p_deque->left = NULL;
	p_deque->right = NULL;
}

int	is_deque_empty(t_deque *p_deque)
{
	if (deque_get_size(p_deque) == 0)
		return (TRUE);
	return (FALSE);
}

int	is_deque_sorted(t_deque *p_a)
{
	int			x;
	t_node		*node;

	x = p_a->right->data;
	node = p_a->right->prev;
	while (node)
	{
		if (node->data > x)
			x = node->data;
		else
			return (FALSE);
		node = node->prev;
	}
	return (TRUE);
}
