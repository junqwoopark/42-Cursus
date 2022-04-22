/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:04:42 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/22 12:13:16 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	deque_pop_left(t_deque *p_deque)
{
	t_node	*node;
	int		data;

	if (is_deque_empty(p_deque))
		exit(1);
	node = p_deque->left;
	data = p_deque->left->data;
	p_deque->left = p_deque->left->next;
	free(node);
	if (p_deque->left == NULL)
		p_deque->right = NULL;
	else
		p_deque->left->prev = NULL;
	return (data);
}

int	deque_pop_right(t_deque *p_deque)
{
	t_node	*node;
	int		data;

	if (is_deque_empty(p_deque))
		exit(1);
	node = p_deque->right;
	data = p_deque->right->data;
	p_deque->right = p_deque->right->prev;
	free(node);
	if (p_deque->right == NULL)
		p_deque->left = NULL;
	else
		p_deque->right->prev = NULL;
	return (data);
}
