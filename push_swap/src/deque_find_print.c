/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_find_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:07:56 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 21:35:52 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*deque_find_data(t_deque *p_deque, int data)
{
	t_node	*ret;

	ret = p_deque->top;
	while (ret)
	{
		if (ret->data == data)
			return (ret);
		ret = ret->under;
	}
	return (ret);
}

void	deque_print_data(t_deque *p_deque)
{
	t_node	*node;

	node = p_deque->bottom;
	while (node)
	{
		ft_putnbr_fd(node->data, 1);
		ft_putchar_fd(' ', 1);
		node = node->over;
	}
	ft_putchar_fd('\n', 1);
}

void	deque_print_result(t_deque *p_deque)
{
	t_node	*node;

	node = p_deque->bottom;
	while (node)
	{
		if (node->data <= RR)
			write(1, &("sasbsspapbrarbrr"[node->data * 2]), 2);
		else
			write(1, &("rrarrbrrr"[(node->data % 8) * 3]), 3);
		ft_putchar_fd('\n', 1);
		node = node->over;
	}
}

int	deque_get_idx_to_top(t_deque *p_deque, int data)
{
	t_node	*node;
	int		idx;

	node = p_deque->top;
	idx = 0;
	while (node)
	{
		if (node->data == data)
			break ;
		node = node->under;
		idx++;
	}
	return (idx);
}
