/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:38:11 by chukim            #+#    #+#             */
/*   Updated: 2021/11/17 14:00:41 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find(char *str, const char *target, size_t len, size_t i);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*str;

	str = (char *)haystack;
	i = 0;
	if (*needle == 0)
		return (str);
	while (str[i])
	{
		if (ft_find(str, needle, len, i) == 0)
			i++;
		else if (ft_find(str, needle, len, i) == 1)
			return (&str[i]);
	}
	return (NULL);
}

static int	ft_find(char *str, const char *target, size_t len, size_t i)
{
	size_t	target_i;

	target_i = 0;
	while (target[target_i])
	{
		if (len <= i)
			return (0);
		if (target[target_i] != str[i])
			return (0);
		i++;
		target_i++;
	}
	return (1);
}
