/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:51:09 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/02 14:19:49 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long long	ret;
	int			sign;

	ret = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			exit_with_error("ft_atoi : is not digit\n");
		ret = ret * 10 + *str - '0';
		if (ret < 0)
			exit_with_error("ft_atoi : overflow\n");
		str++;
	}
	return (ret * sign);
}
