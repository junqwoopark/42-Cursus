/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:31:26 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/24 20:37:27 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deque_del(t_deque *deque, t_node *node)
{
	t_node	*over;
	t_node	*under;

	if (node == deque->top)
		deque_pop_top(deque);
	else if (node == deque->bottom)
		deque_pop_bottom(deque);
	else
	{
		over = node->over;
		under = node->under;
		deque->size -= 1;
		free(node);
		over->under = under;
		under->over = over;
	}
}
