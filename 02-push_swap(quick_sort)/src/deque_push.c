/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:02:01 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 21:35:52 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deque_push_bottom(t_deque *p_deque, int data)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		exit(1);
	new_node->data = data;
	new_node->over = p_deque->bottom;
	new_node->under = NULL;
	if (is_deque_empty(p_deque))
		p_deque->top = new_node;
	else
		p_deque->bottom->under = new_node;
	p_deque->bottom = new_node;
	p_deque->size += 1;
}

void	deque_push_top(t_deque *p_deque, int data)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		exit(1);
	new_node->data = data;
	new_node->under = p_deque->top;
	new_node->over = NULL;
	if (is_deque_empty(p_deque))
		p_deque->bottom = new_node;
	else
		p_deque->top->over = new_node;
	p_deque->top = new_node;
	p_deque->size += 1;
}
