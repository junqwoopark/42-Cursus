/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:21:51 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:58:06 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_data *data)
{
	int	first_data;
	int	second_data;

	first_data = deque_pop_back(&data->a);
	second_data = deque_pop_back(&data->a);
	deque_push_back(&data->a, first_data);
	deque_push_back(&data->a, second_data);
	deque_push_back(&data->result, SA);
}

void	sb(t_data *data)
{
	int	first_data;
	int	second_data;

	first_data = deque_pop_back(&data->b);
	second_data = deque_pop_back(&data->b);
	deque_push_back(&data->b, first_data);
	deque_push_back(&data->b, second_data);
	deque_push_back(&data->result, SB);
}

void	ss(t_data *data)
{
	sa(data);
	sb(data);
	deque_pop_back(&data->result);
	deque_pop_back(&data->result);
	deque_push_back(&data->result, SS);
}
