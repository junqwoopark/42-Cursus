/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 08:34:18 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/18 13:04:48 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	idx;
	char	*dest;
	char	*source;

	dest = (char *) dst;
	source = (char *) src;
	if (dest == source)
		return (dest);
	idx = 0;
	while (idx < n)
	{
		*dest = *source;
		dest++;
		source++;
		idx++;
	}
	return (dst);
}
