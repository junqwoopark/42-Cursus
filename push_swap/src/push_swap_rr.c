/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:27:31 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/24 17:17:59 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_data *data)
{
	int	bottom;

	bottom = deque_pop_bottom(&data->a);
	deque_push_top(&data->a, bottom);
	deque_push_top(&data->to_print, RRA);
}

void	rrb(t_data *data)
{
	int	bottom;

	bottom = deque_pop_bottom(&data->b);
	deque_push_top(&data->b, bottom);
	deque_push_top(&data->to_print, RRB);
}

void	rrr(t_data *data)
{
	rra(data);
	rrb(data);
	deque_pop_top(&data->to_print);
	deque_pop_top(&data->to_print);
	deque_push_top(&data->to_print, RRR);
}
