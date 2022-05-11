/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:35:25 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/10 14:31:39 by junkpark         ###   ########.fr       */
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
	long long	x;
	t_node		*node;

	x = LONG_MIN;
	node = p_a->right;
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
