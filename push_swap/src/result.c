/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:43:44 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:53:56 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	optimize_result(t_deque *result)
{
	t_node	*node;

	node = result->front;
	while (node && node->next)
	{
		if ((node->data == SA && node->next->data == SB)
			|| (node->data == SB && node->next->data == SA))
		{
			node->data = SS;
			deque_del(result, node->next);
		}
		else if ((node->data == RA && node->next->data == RB)
			|| (node->data == RB && node->next->data == RA))
		{
			node->data = RR;
			deque_del(result, node->next);
		}
		else if ((node->data == RRA && node->next->data == RRB)
			|| (node->data == RRB && node->next->data == RRA))
		{
			node->data = RRR;
			deque_del(result, node->next);
		}
		node = node->next;
	}
}

void	print_result(t_deque *result)
{
	t_node	*node;

	node = result->front;
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
