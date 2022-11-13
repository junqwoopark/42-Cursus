/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:43:21 by chukim            #+#    #+#             */
/*   Updated: 2021/11/17 13:16:46 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	target;

	target = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (target == s[i])
			return ((char *)(&s[i]));
		i++;
	}
	if (target == s[i])
		return ((char *)(&s[i]));
	return (NULL);
}
