/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 08:34:18 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/16 23:46:04 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t	idx;
	char	*dest;
	char	*source;

	dest = (char *) dst;
	source = (char *) src;
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
