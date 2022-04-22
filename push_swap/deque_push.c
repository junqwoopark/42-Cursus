/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:02:01 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/22 12:02:08 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deque_push_left(t_deque *p_deque, int data)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		exit(1);
	new_node->data = data;
	new_node->next = p_deque->left;
	if (is_deque_empty(p_deque))
		p_deque->right = new_node;
	else
		p_deque->left->prev = new_node;
	new_node->prev = NULL;
	p_deque->left = new_node;
}

void	deque_push_right(t_deque *p_deque, int data)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		exit(1);
	new_node->data = data;
	new_node->next = p_deque->right;
	if (is_deque_empty(p_deque))
		p_deque->right = new_node;
	else
		p_deque->right->next = new_node;
	new_node->next = NULL;
	p_deque->right = new_node;
}
