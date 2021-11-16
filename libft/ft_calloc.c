/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:14:39 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/16 15:11:36 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ret;
	unsigned char	*tmp;
	size_t			idx;
	size_t			len;

	len = count * size;
	ret = malloc(len);
	tmp = (unsigned char *) ret;
	if (ret == 0)
		return (ret);
	idx = 0;
	while (idx < len)
	{
		tmp[idx] = 0;
		idx++;
	}
	return (ret);
}
