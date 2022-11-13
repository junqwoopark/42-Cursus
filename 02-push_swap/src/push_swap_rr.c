/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:27:31 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:58:06 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_data *data)
{
	int	front;

	front = deque_pop_front(&data->a);
	deque_push_back(&data->a, front);
	deque_push_back(&data->result, RRA);
}

void	rrb(t_data *data)
{
	int	front;

	front = deque_pop_front(&data->b);
	deque_push_back(&data->b, front);
	deque_push_back(&data->result, RRB);
}

void	rrr(t_data *data)
{
	rra(data);
	rrb(data);
	deque_pop_back(&data->result);
	deque_pop_back(&data->result);
	deque_push_back(&data->result, RRR);
}
