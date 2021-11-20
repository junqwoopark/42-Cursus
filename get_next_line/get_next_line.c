/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:48:02 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/20 18:23:53 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	update_buff(char *s_buff, size_t idx)
{
	if (s_buff[idx] == '\n')
	{
		ft_strlcpy(s_buff, &(s_buff[idx + 1]), BUFFER_SIZE + 1);
		return (1);
	}
	ft_strlcpy(s_buff, &(s_buff[idx + 1]), BUFFER_SIZE + 1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	s_buff[BUFFER_SIZE + 1];
	char		*ret;
	char		*tmp;
	size_t		idx;

	ret = NULL;
	tmp = ft_calloc(1, 1);
	while (ft_strlen(s_buff) >= 1 || read(fd, s_buff, BUFFER_SIZE) > 0)
	{
		idx = 0;
		while (s_buff[idx] != '\n' && s_buff[idx] != 0)
			idx++;
		ret = (char *)malloc(ft_strlen(tmp) + idx + 1);
		if (ret == NULL)
			return (NULL);
		ft_strlcpy(ret, tmp, ft_strlen(tmp) + 1);
		ft_strlcat(ret, s_buff, ft_strlen(tmp) + idx + 1);
		free(tmp);
		tmp = ret;
		if (update_buff(s_buff, idx))
			return (ret);
	}
	return (ret);
}
