/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:56:29 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/29 17:26:12 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
