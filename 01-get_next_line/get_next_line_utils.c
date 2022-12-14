/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:56:06 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/08 19:51:08 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	ret;

	ret = 0;
	while (s[ret])
		ret++;
	return (ret);
}

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
	while (idx < len)
	{
		dest[idx] = 0;
		idx++;
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	idx;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	idx = 0;
	if (size < dst_len + 1)
		return (size + src_len);
	if (size > dst_len + 1)
	{
		while (src[idx] && dst_len + 1 + idx < size)
		{
			dst[dst_len + idx] = src[idx];
			idx++;
		}
	}
	dst[dst_len + idx] = 0;
	return (dst_len + src_len);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	ret = (char *)malloc(len + 1);
	if (ret == 0)
		return (ret);
	ft_strlcpy(ret, s1, len + 1);
	return (ret);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ret;
	size_t			len;
	size_t			idx;

	len = count * size;
	ret = malloc(len);
	if (ret == 0)
		return (ret);
	idx = 0;
	while (idx < len)
	{
		((unsigned char *)ret)[idx] = 0;
		idx++;
	}
	if (len == 0)
		((unsigned char *)ret)[0] = 0;
	return (ret);
}
