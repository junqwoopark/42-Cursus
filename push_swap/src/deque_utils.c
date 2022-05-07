/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:35:25 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/02 17:26:01 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deque_init(t_deque **p_deque)
{
	*p_deque = (t_deque *)malloc(sizeof(t_deque));
	if (p_deque == NULL)
		exit(1);
	(*p_deque)->size = 0;
	(*p_deque)->left = NULL;
	(*p_deque)->right = NULL;
}

int	deque_get_size(t_deque *p_deque)
{
	return (p_deque->size);
}

int	is_deque_empty(t_deque *p_deque)
{
	if (deque_get_size(p_deque) == 0)
		return (TRUE);
	return (FALSE);
}

int	deque_get_left(t_deque *p_deque)
{
	if (is_deque_empty(p_deque))
		exit(1);
	return (p_deque->left->data);
}

int	deque_get_right(t_deque *p_deque)
{
	if (is_deque_empty(p_deque))
		exit(1);
	return (p_deque->right->data);
}
