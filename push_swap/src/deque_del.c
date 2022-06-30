/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:31:26 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:14:07 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deque_del(t_deque *deque, t_node *node)
{
	t_node	*next;
	t_node	*prev;

	if (node == deque->back)
		deque_pop_back(deque);
	else if (node == deque->front)
		deque_pop_front(deque);
	else
	{
		next = node->next;
		prev = node->prev;
		deque->size -= 1;
		free(node);
		next->prev = prev;
		prev->next = next;
	}
}
