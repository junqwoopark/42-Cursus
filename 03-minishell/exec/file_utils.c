/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:07:55 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 17:26:11 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	if (fd == 0 || fd == 1 || fd == 2)
		return ;
	close(fd);
}

void	ft_dup2(int fd1, int fd2)
{
	if (fd1 == 0 || fd1 == 1 || fd1 == 2)
		return ;
	dup2(fd1, fd2);
	ft_close(fd1);
}

int	is_excutable(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (0);
	if (S_ISDIR(sb.st_mode))
	{
		errno = EISDIR;
		return (0);
	}
	if (sb.st_mode & S_IXUSR)
		return (1);
	else
		errno = EACCES;
	return (0);
}
