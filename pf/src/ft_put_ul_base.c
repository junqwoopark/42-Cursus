/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ul_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:35:14 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/11 23:59:58 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_put_ul_base(unsigned long nbr, char *base)
{
	int		base_len;
	char	str[100];
	int		ret;
	int		idx;

	base_len = ft_strlen(base);
	idx = 0;
	if (nbr == 0)
	{
		ft_putchar_fd(base[0], 1);
		return (1);
	}
	while (nbr)
	{
		str[idx] = base[nbr % base_len];
		nbr = nbr / base_len;
		idx++;
	}
	ret = idx;
	while (--idx >= 0)
		ft_putchar_fd(str[idx], 1);
	return (ret);
}
