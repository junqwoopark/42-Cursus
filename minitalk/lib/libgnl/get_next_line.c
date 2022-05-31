/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:48:02 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/08 22:08:27 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	update_buff(char *buff, size_t idx)
{
	int	x;

	x = 0;
	if (idx >= BUFFER_SIZE)
	{
		while (x < BUFFER_SIZE)
			buff[x++] = 0;
		return (0);
	}
	else
	{
		if (buff[idx] == '\n')
		{
			ft_buffcpy(buff, idx);
			return (1);
		}
		ft_buffcpy(buff, idx);
		return (0);
	}
}

void	ft_buffcpy(char	*buff, size_t idx)
{
	int	i;

	i = 0;
	if (buff[idx] == '\n')
		idx++;
	while (i < BUFFER_SIZE && idx < BUFFER_SIZE)
	{
		buff[i] = buff[idx];
		i++;
		idx++;
	}
	while (i < BUFFER_SIZE)
		buff[i++] = 0;
}

void	ft_cpycat(char	*dst, char *src1, char *src2, size_t idx)
{
	ft_strlcpy(dst, src1, ft_strlen(src1) + 1);
	if (idx < BUFFER_SIZE && src2[idx] == '\n')
		ft_strlcat(dst, src2, ft_strlen(src1) + idx + 2);
	else
		ft_strlcat(dst, src2, ft_strlen(src1) + idx + 1);
	free(src1);
}

char	*malloc_ret(char *tmp, char *buff, size_t *idx)
{
	char	*ret;

	*idx = 0;
	while (*idx < BUFFER_SIZE && buff[*idx] != '\n' && buff[*idx] != 0)
		(*idx)++;
	if (*idx < BUFFER_SIZE && buff[*idx] == '\n')
		ret = (char *)malloc(ft_strlen(tmp) + *idx + 2);
	else
		ret = (char *)malloc(ft_strlen(tmp) + *idx + 1);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	char		*ret;
	char		*tmp;
	size_t		idx;

	ret = NULL;
	tmp = ft_calloc(1, 1);
	if (!tmp)
		return (NULL);
	while (ft_bufflen(buff) >= 1 || read(fd, buff, BUFFER_SIZE) > 0)
	{
		ret = malloc_ret(tmp, buff, &idx);
		if (ret == NULL)
		{
			free(tmp);
			return (NULL);
		}
		ft_cpycat(ret, tmp, buff, idx);
		tmp = ret;
		if (update_buff(buff, idx))
			return (ret);
	}
	if (!ret)
		free(tmp);
	return (ret);
}
