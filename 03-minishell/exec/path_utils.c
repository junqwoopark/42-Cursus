/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:04:09 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 19:03:02 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_path(char *envp[])
{
	char	*path;

	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (*envp == NULL)
		return (NULL);
	path = *envp + 5;
	return (ft_split(path, ':'));
}

int	is_cmd_contain_slash(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->argv[0][i])
	{
		if (cmd->argv[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*get_cmd_path(char *path[], t_cmd *cmd)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	if (is_cmd_contain_slash(cmd) || path == NULL)
	{
		if (is_excutable(cmd->argv[0]) == 0)
			return (NULL);
		return (ft_strdup(cmd->argv[0]));
	}
	tmp = ft_strjoin("/", cmd->argv[0]);
	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], tmp);
		if (is_excutable(cmd_path))
		{
			free(tmp);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(tmp);
	return (NULL);
}
