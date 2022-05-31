/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:14:39 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/16 19:52:10 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				idx;
	const unsigned char	*str;

	str = (const unsigned char *)s;
	idx = 0;
	while (idx < n)
	{
		if (str[idx] == (unsigned char)c)
			return ((void *)&(str[idx]));
		idx++;
	}
	return (0);
}
