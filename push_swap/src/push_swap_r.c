/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:27:31 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:58:06 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_data *data)
{
	int	back;

	back = deque_pop_back(&data->a);
	deque_push_front(&data->a, back);
	deque_push_back(&data->result, RA);
}

void	rb(t_data *data)
{
	int	back;

	back = deque_pop_back(&data->b);
	deque_push_front(&data->b, back);
	deque_push_back(&data->result, RB);
}

void	rr(t_data *data)
{
	ra(data);
	rb(data);
	deque_pop_back(&data->result);
	deque_pop_back(&data->result);
	deque_push_back(&data->result, RR);
}
