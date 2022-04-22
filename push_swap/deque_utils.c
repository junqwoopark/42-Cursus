/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:35:25 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/22 12:13:27 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deque_init(t_deque *p_deque)
{
	p_deque->left = NULL;
	p_deque->right = NULL;
}

int	is_deque_empty(t_deque *p_deque)
{
	if (p_deque->left)
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
