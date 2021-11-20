/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:48:02 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/20 18:47:06 by junkpark         ###   ########.fr       */
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

void	ft_cpycat(char	*dst, char *src1, char *src2, size_t idx)
{
	ft_strlcpy(dst, src1, ft_strlen(src1) + 1);
	ft_strlcat(dst, src2, ft_strlen(src1) + idx + 1);
	free(src1);
}

char	*free_tmp(char *tmp)
{
	free(tmp);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	s_buff[BUFFER_SIZE + 1];
	char		*ret;
	char		*tmp;
	size_t		idx;

	ret = NULL;
	tmp = ft_calloc(1, 1);
	if (!tmp)
		return (NULL);
	while (ft_strlen(s_buff) >= 1 || read(fd, s_buff, BUFFER_SIZE) > 0)
	{
		idx = 0;
		while (s_buff[idx] != '\n' && s_buff[idx] != 0)
			idx++;
		ret = (char *)malloc(ft_strlen(tmp) + idx + 1);
		if (ret == NULL)
			return (free_tmp(tmp));
		ft_cpycat(ret, tmp, s_buff, idx);
		tmp = ret;
		if (update_buff(s_buff, idx))
			return (ret);
	}
	return (ret);
}
