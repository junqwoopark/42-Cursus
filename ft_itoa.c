/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:14:39 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/16 18:15:58 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strrev(char *str)
{
	size_t	idx;
	size_t	len;
	char	tmp;

	len = ft_strlen(str);
	idx = 0;
	while (idx * 2 < len)
	{
		tmp = str[idx];
		str[idx] = str[len - 1 - idx];
		str[len - 1 - idx] = tmp;
		idx++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t			size;
	unsigned int	tmp;
	char			num[11];
	char			minus[2];

	ft_memset(num, 0, 11);
	ft_memset(minus, 0, 2);
	tmp = n;
	if (n < 0)
	{
		tmp = -n;
		minus[0] = '-';
	}
	size = 0;
	num[0] = '0';
	while (tmp / 10 || tmp % 10)
	{
		num[size] = tmp % 10 + '0';
		tmp /= 10;
		size += 1;
	}
	ft_strrev(num);
	return (ft_strjoin(minus, num));
}
