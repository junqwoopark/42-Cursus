/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:21:51 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/24 17:32:26 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_data *data)
{
	int	first_data;
	int	second_data;

	first_data = deque_pop_top(&data->a);
	second_data = deque_pop_top(&data->a);
	deque_push_top(&data->a, first_data);
	deque_push_top(&data->a, second_data);
	deque_push_top(&data->to_print, SA);
}

void	sb(t_data *data)
{
	int	first_data;
	int	second_data;

	first_data = deque_pop_top(&data->b);
	second_data = deque_pop_top(&data->b);
	deque_push_top(&data->b, first_data);
	deque_push_top(&data->b, second_data);
	deque_push_top(&data->to_print, SB);
}

void	ss(t_data *data)
{
	sa(data);
	sb(data);
	deque_pop_top(&data->to_print);
	deque_pop_top(&data->to_print);
	deque_push_top(&data->to_print, SS);
}
