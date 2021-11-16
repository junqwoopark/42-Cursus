/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 23:14:39 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/16 22:13:03 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	**ft_free(char **strs, size_t count)
{
	size_t	idx;

	idx = 0;
	while (idx < count + 1)
	{
		free(strs[idx]);
		idx++;
	}
	free(strs);
	return (0);
}

static size_t	ft_get_count(char const *s, char c)
{
	size_t	ret;
	size_t	i;

	ret = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s == 0)
			return (ret);
		i = 0;
		while (s[i] != c && s[i])
			i++;
		ret += 1;
		s = s + i;
	}
	return (ret);
}

static char	**ft_get_split(char const *s, char c, size_t count, char **strs)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	strs[count] = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s == 0)
			return (strs);
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		str = (char *)malloc(i + 1);
		if (str == 0)
			return (ft_free(strs, count));
		ft_strlcpy(str, s, i + 1);
		strs[j++] = str;
		s = s + i;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**strs;

	count = ft_get_count(s, c);
	strs = (char **) malloc(sizeof(char *) * (count + 1));
	if (strs == 0)
		return (0);
	return (ft_get_split(s, c, count, strs));
}
