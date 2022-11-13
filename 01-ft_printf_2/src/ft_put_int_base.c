/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_int_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:51:30 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/14 02:09:55 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_put_int_base(int nbr, char *base)
{
	int	ret;

	ret = 0;
	if (nbr == -2147483648)
		return (ft_put_str("-2147483648"));
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		nbr = -nbr;
		ret++;
	}
	ret += ft_put_ul_base(nbr, base);
	return (ret);
}
