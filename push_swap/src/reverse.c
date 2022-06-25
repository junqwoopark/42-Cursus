/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:56:29 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/25 16:53:48 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_instance(t_instance *instance, int start, int size)
{
	ft_bzero(instance, sizeof(t_instance));
	instance->size = size;
	instance->pivots.min = start + size / 3;
	instance->pivots.max = start + size / 3 * 2;
}

void	reverse(int ra_cnt, int rb_cnt, t_data *data)
{
	while (ra_cnt && rb_cnt)
	{
		rrr(data);
		ra_cnt--;
		rb_cnt--;
	}
	while (ra_cnt)
	{
		rra(data);
		ra_cnt--;
	}
	while (rb_cnt)
	{
		rrb(data);
		rb_cnt--;
	}
}
