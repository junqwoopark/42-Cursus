/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:35:25 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 21:35:33 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deque_init(t_deque *p_deque)
{
	p_deque->size = 0;
	p_deque->bottom = NULL;
	p_deque->top = NULL;
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

	x = p_a->top->data;
	node = p_a->top->under;
	while (node)
	{
		if (node->data > x)
			x = node->data;
		else
			return (FALSE);
		node = node->under;
	}
	return (TRUE);
}
