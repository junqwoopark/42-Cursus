/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:37:56 by chukim            #+#    #+#             */
/*   Updated: 2021/11/16 13:04:45 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;

	if (dst == src || len == 0)
		return (dst);
	if (dst < src)
	{
		dst_tmp = (unsigned char *)dst;
		src_tmp = (unsigned char *)src;
		while (len--)
			*dst_tmp++ = *src_tmp++;
	}
	else
	{
		dst_tmp = (unsigned char *)dst + (len - 1);
		src_tmp = (unsigned char *)src + (len - 1);
		while (len--)
			*dst_tmp-- = *src_tmp--;
	}
	return (dst);
}
