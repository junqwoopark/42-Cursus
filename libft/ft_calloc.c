/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:14:39 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/18 13:57:42 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ret;
	size_t			len;

	len = count * size;
	ret = malloc(len);
	if (ret == 0)
		return (ret);
	ft_bzero(ret, len);
	if (len == 0)
		((unsigned char *)ret)[0] = 0;
	return (ret);
}
