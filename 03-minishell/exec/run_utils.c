/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:02:49 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/04 17:05:13 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0
		|| ft_strcmp(cmd->argv[0], "echo") == 0
		|| ft_strcmp(cmd->argv[0], "pwd") == 0
		|| ft_strcmp(cmd->argv[0], "export") == 0
		|| ft_strcmp(cmd->argv[0], "unset") == 0
		|| ft_strcmp(cmd->argv[0], "env") == 0
		|| ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}

void	run_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(cmd);
	else
		return ;
}

void	run_builtin_multiple_cmd(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit_multiple_cmd(cmd);
	else
		return ;
}

void	run_cmd(t_cmd *cmd)
{
	char	*cmd_path;
	char	**env_path;

	if (is_builtin(cmd))
	{
		run_builtin_multiple_cmd(cmd);
		exit(g_errno);
	}
	env_path = get_env_path(cmd->envp_copy_arr);
	cmd_path = get_cmd_path(env_path, cmd);
	if (env_path != NULL)
		free_env_path(&env_path);
	if (cmd_path)
	{
		free(cmd->argv[0]);
		cmd->argv[0] = cmd_path;
		execve(cmd_path, cmd->argv, cmd->envp_copy_arr);
	}
	else if (!is_cmd_contain_slash(cmd) && env_path != NULL)
		exit_with_err(cmd->argv[0], "command not found", 127, 1);
	else if (errno == EISDIR || errno == EACCES)
		exit_with_err(cmd->argv[0], strerror(errno), 126, 1);
	else
		exit_with_err(cmd->argv[0], strerror(errno), 127, 1);
}
