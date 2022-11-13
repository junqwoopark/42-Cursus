/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:04:42 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:14:07 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	deque_pop_front(t_deque *p_deque)
{
	t_node	*node;
	int		data;

	if (is_deque_empty(p_deque))
		exit(1);
	node = p_deque->front;
	data = p_deque->front->data;
	p_deque->front = p_deque->front->next;
	p_deque->size -= 1;
	free(node);
	if (p_deque->front == NULL)
		p_deque->back = NULL;
	else
		p_deque->front->prev = NULL;
	return (data);
}

int	deque_pop_back(t_deque *p_deque)
{
	t_node	*node;
	int		data;

	if (is_deque_empty(p_deque))
		exit(1);
	node = p_deque->back;
	data = p_deque->back->data;
	p_deque->back = p_deque->back->prev;
	p_deque->size -= 1;
	free(node);
	if (p_deque->back == NULL)
		p_deque->front = NULL;
	else
		p_deque->back->next = NULL;
	return (data);
}
