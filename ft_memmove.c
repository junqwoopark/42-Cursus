/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:22:34 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/16 23:04:44 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	size_t			idx;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	idx = 0;
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
		while (idx < len)
		{
			dest[idx] = source[idx];
			idx++;
		}
	}
	return (dst);
}
