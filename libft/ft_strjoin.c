/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:13:18 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/16 18:06:36 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *) malloc(len + 1);
	if (ret == 0)
		return (ret);
	ret[0] = 0;
	ft_strlcat(ret, s1, len + 1);
	ft_strlcat(ret, s2, len + 1);
	return (ret);
}
