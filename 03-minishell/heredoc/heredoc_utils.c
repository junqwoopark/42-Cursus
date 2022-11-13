/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:39:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/04 18:36:35 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_delimiter_to_file_name(t_cmd *cmd)
{
	int		i;
	int		j;
	size_t	tmp_file_cnt;

	i = 0;
	tmp_file_cnt = 0;
	while (cmd[i].token)
	{
		j = 0;
		while (cmd[i].token[j].type)
		{
			if (cmd[i].token[j].type == T_REDIRECT
				&& ft_strcmp(cmd[i].token[j].str, "<<") == 0)
			{
				free(cmd[i].token[j + 1].str);
				cmd[i].token[j + 1].str = get_tmp_file_path(tmp_file_cnt);
				tmp_file_cnt += 1;
			}
			j++;
		}
		i++;
	}
}

char	*get_tmp_file_path(size_t tmp_file_cnt)
{
	char	*tmp;
	char	*tmp_file_path;

	tmp_file_path = "/tmp/tmpfile_minishell_";
	tmp = ft_itoa(tmp_file_cnt);
	tmp_file_path = ft_strjoin(tmp_file_path, tmp);
	free(tmp);
	return (tmp_file_path);
}

void	clear_file(int fd, char *tmp_file_path, size_t tmp_file_cnt)
{
	size_t	i;

	close(fd);
	fd = open(tmp_file_path, O_WRONLY | O_CREAT | O_TRUNC, 420);
	close(fd);
	printf("\001\e[1A\002");
	i = 0;
	while (i <= tmp_file_cnt)
	{
		printf("\001\e[2C\002");
		i++;
	}
}
