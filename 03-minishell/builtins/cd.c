/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:36:09 by chukim            #+#    #+#             */
/*   Updated: 2022/08/04 19:53:10 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_env *envp)
{
	char	*old_pwd;
	char	*cur_pwd;
	char	*tmp;

	tmp = calloc(4096, sizeof(char));
	cur_pwd = ft_strjoin("PWD=", getcwd(tmp, 4096));
	old_pwd = ft_strjoin("OLDPWD=", get_env(envp, "PWD"));
	add_or_update_env(cur_pwd, envp);
	add_or_update_env(old_pwd, envp);
	free(tmp);
	free(cur_pwd);
	free(old_pwd);
}

void	cd_home(t_cmd *cmd)
{
	char	*path;

	path = get_env(cmd->envp_copy, "HOME");
	if (cmd->argv[1] == NULL)
	{
		if (chdir(path) == -1
			&& (strcmp(get_env(cmd->envp_copy, "HOME"), "") == 0))
			exit_with_err("cd", "HOME not set", 1, 0);
		else if (chdir(path) == -1)
			exit_with_err_second("cd", path, "No such file or directory", 1);
		else
			g_errno = 0;
	}
	else
	{
		if (chdir(getenv("HOME")) == -1)
			exit_with_err_second("cd", path, "No such file or directory", 1);
		else
			g_errno = 0;
	}
}

void	ft_cd(t_cmd *cmd)
{
	char	*path;

	if (cmd->argv[1] != NULL)
	{
		path = cmd->argv[1];
		if (chdir(path) == -1)
			exit_with_err_second("cd", path, strerror(errno), 1);
		else
			g_errno = 0;
		set_pwd(cmd->envp_copy);
	}
	else if (cmd->argv[1] == NULL)
		cd_home(cmd);
}
