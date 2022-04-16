/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:22:34 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/17 00:30:48 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*source;
	size_t	idx;

	dest = (char *)dst;
	source = (char *)src;
	if (src < dst)
	{
		while (len)
		{
			dest[len - 1] = source[len - 1];
			len--;
		}
	}
	else if (src > dst)
	{
		idx = 0;
		while (idx < len)
		{
			dest[idx] = source[idx];
			idx++;
		}
	}
	return (dst);
}
