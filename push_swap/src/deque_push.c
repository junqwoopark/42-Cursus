/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:02:01 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:14:07 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deque_push_front(t_deque *p_deque, int data)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		exit(1);
	new_node->data = data;
	new_node->next = p_deque->front;
	new_node->prev = NULL;
	if (is_deque_empty(p_deque))
		p_deque->back = new_node;
	else
		p_deque->front->prev = new_node;
	p_deque->front = new_node;
	p_deque->size += 1;
}

void	deque_push_back(t_deque *p_deque, int data)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		exit(1);
	new_node->data = data;
	new_node->prev = p_deque->back;
	new_node->next = NULL;
	if (is_deque_empty(p_deque))
		p_deque->front = new_node;
	else
		p_deque->back->next = new_node;
	p_deque->back = new_node;
	p_deque->size += 1;
}
