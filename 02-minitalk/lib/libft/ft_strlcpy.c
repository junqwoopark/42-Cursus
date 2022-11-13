/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:22:34 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/16 18:32:52 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(void *dst, const void *src, size_t len)
{
	size_t			idx;
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	idx = 0;
	if (len == 0)
		return (ft_strlen(src));
	while (idx + 1 < len && source[idx])
	{
		dest[idx] = source[idx];
		idx++;
	}
	dest[idx] = 0;
	return (ft_strlen(src));
}
