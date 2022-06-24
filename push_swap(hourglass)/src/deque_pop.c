/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:04:42 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 21:35:52 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	deque_pop_bottom(t_deque *p_deque)
{
	t_node	*node;
	int		data;

	if (is_deque_empty(p_deque))
		exit(1);
	node = p_deque->bottom;
	data = p_deque->bottom->data;
	p_deque->bottom = p_deque->bottom->over;
	p_deque->size -= 1;
	free(node);
	if (p_deque->bottom == NULL)
		p_deque->top = NULL;
	else
		p_deque->bottom->under = NULL;
	return (data);
}

int	deque_pop_top(t_deque *p_deque)
{
	t_node	*node;
	int		data;

	if (is_deque_empty(p_deque))
		exit(1);
	node = p_deque->top;
	data = p_deque->top->data;
	p_deque->top = p_deque->top->under;
	p_deque->size -= 1;
	free(node);
	if (p_deque->top == NULL)
		p_deque->bottom = NULL;
	else
		p_deque->top->over = NULL;
	return (data);
}
