/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:27:31 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/24 17:22:34 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_data *data)
{
	int	top;

	top = deque_pop_top(&data->a);
	deque_push_bottom(&data->a, top);
	deque_push_top(&data->to_print, RA);
}

void	rb(t_data *data)
{
	int	top;

	top = deque_pop_top(&data->b);
	deque_push_bottom(&data->b, top);
	deque_push_top(&data->to_print, RB);
}

void	rr(t_data *data)
{
	ra(data);
	rb(data);
	deque_pop_top(&data->to_print);
	deque_pop_top(&data->to_print);
	deque_push_top(&data->to_print, RR);
}
