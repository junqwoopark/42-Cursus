/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:15:53 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/24 17:35:56 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_data *data)
{
	int	top;

	top = deque_pop_top(&data->b);
	deque_push_top(&data->a, top);
	deque_push_top(&data->to_print, PA);
}

void	pb(t_data *data)
{
	int	top;

	top = deque_pop_top(&data->a);
	deque_push_top(&data->b, top);
	deque_push_top(&data->to_print, PB);
}
