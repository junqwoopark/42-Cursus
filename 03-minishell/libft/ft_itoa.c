/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:58:19 by chukim            #+#    #+#             */
/*   Updated: 2022/08/03 19:23:46 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n, int *sign);
static void	ft_put(char *str, int len, int n);

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		len;

	sign = 0;
	len = ft_len(n, &sign);
	str = (char *)ft_calloc(sizeof(char), (len + sign + 1));
	if (str == NULL)
		return (NULL);
	str[len + sign] = '\0';
	if (n == -2147483648)
	{
		str[10] = '8';
		n = 214748364;
		str[0] = '-';
		len--;
	}
	else if (sign == 1)
	{
		str[0] = '-';
		n = -n;
	}
	ft_put(&str[sign], len, n);
	return (&str[0]);
}

static int	ft_len(int n, int *sign)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			*sign = 1;
			return (10);
		}
		else
		{
			*sign = 1;
			n = -n;
		}
	}
	else if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	ft_put(char *str, int len, int n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		str[i] = '0';
	}
	while (n)
	{
		str[len - i - 1] = n % 10 + '0';
		n = n / 10;
		i++;
	}
}
