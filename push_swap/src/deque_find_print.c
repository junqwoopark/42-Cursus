/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_find_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:07:56 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/11 09:43:38 by junkpark         ###   ########.fr       */
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

void	deque_print_char(t_deque *p_deque)
{
	t_node	*node;

	node = p_deque->left;
	while (node)
	{
		if (node->data <= RR)
			write(1, &("sasbsspapbrarbrr"[node->data * 2]), 2);
		else
			write(1, &("rrarrbrrr"[(node->data % 8) * 3]), 3);
		ft_putchar_fd('\n', 1);
		node = node->next;
	}
}

int	deque_get_idx_to_top(t_deque *p_deque, int data)
{
	t_node	*node;
	int		idx;

	node = p_deque->right;
	idx = 0;
	while (node)
	{
		if (node->data == data)
			break ;
		node = node->prev;
		idx++;
	}
	return (idx);
}
