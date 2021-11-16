/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:13:18 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/17 00:11:20 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	back;
	size_t	size;
	char	*ret;

	if (!s1 || !set)
		return (0);
	front = 0;
	back = ft_strlen(s1);
	while (front < back && ft_isinset(s1[front], set))
		front++;
	while (1 <= back && ft_isinset(s1[back - 1], set))
		back--;
	if (front >= back)
		size = 0;
	else
		size = back - front;
	ret = (char *)malloc(size + 1);
	if (ret == 0)
		return (ret);
	ft_strlcpy(ret, &(s1[front]), size + 1);
	return (ret);
}
