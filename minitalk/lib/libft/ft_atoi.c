/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:51:47 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/25 10:25:40 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == '\f' || c == '\r' || c == ' ' || c == '\t' || c == '\v'
		|| c == '\n')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long long	ret;
	int			sign;

	ret = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		ret = ret * 10 + *str - '0';
		if (ret < 0)
			return ((-1 * sign - 1) / 2);
		str++;
	}
	return (ret * sign);
}
