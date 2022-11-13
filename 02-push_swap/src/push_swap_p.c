/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:15:53 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:58:06 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_data *data)
{
	int	back;

	back = deque_pop_back(&data->b);
	deque_push_back(&data->a, back);
	deque_push_back(&data->result, PA);
}

void	pb(t_data *data)
{
	int	back;

	back = deque_pop_back(&data->a);
	deque_push_back(&data->b, back);
	deque_push_back(&data->result, PB);
}
