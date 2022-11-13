/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:38:31 by chukim            #+#    #+#             */
/*   Updated: 2022/08/04 20:08:33 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_deletespace(char const *str, int *i);

int	ft_atoi(char const *str)
{
	unsigned long long	res;
	int					i;
	int					sign;

	res = 0;
	i = 0;
	sign = 1;
	ft_deletespace(str, &i);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		if (res > 9223372036854775807)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		i++;
	}
	return ((int)res * sign);
}

int	ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\f' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}

static void	ft_deletespace(char const *str, int *i)
{
	while (ft_isspace(str[*i]) == 1)
		(*i)++;
}
