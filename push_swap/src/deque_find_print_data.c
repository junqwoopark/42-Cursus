/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_find_print_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:07:56 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/07 19:45:06 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*deque_find_data(t_deque *p_deque, int data)
{
	t_node	*ret;

	ret = p_deque->right;
	while (ret)
	{
		if (ret->data == data)
			return (ret);
		ret = ret->prev;
	}
	return (ret);
}

void	deque_print_data(t_deque *p_deque)
{
	t_node	*node;

	node = p_deque->left;
	while (node)
	{
		ft_putnbr_fd(node->data, 1);
		ft_putchar_fd(' ', 1);
		node = node->next;
	}
	ft_putchar_fd('\n', 1);
}
