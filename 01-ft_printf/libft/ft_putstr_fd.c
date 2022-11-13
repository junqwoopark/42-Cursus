/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:57:56 by junkpark          #+#    #+#             */
/*   Updated: 2022/04/05 22:42:58 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	ret;

	ret = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		write(fd, s, 1);
		s++;
		ret++;
	}
	return (ret);
}
