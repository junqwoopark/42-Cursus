/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:49:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/04 18:38:13 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_one(t_token *delimiter_token, size_t tmp_file_cnt)
{
	int		fd;
	char	*tmp;
	char	*tmp_file_path;

	tmp_file_path = get_tmp_file_path(tmp_file_cnt);
	fd = open(tmp_file_path, O_WRONLY | O_CREAT | O_TRUNC, 420);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			clear_file(fd, tmp_file_path, tmp_file_cnt);
			break ;
		}
		if (ft_strcmp(tmp, delimiter_token->str) == 0)
		{
			free(tmp);
			break ;
		}
		ft_putendl_fd(tmp, fd);
		free(tmp);
	}
	close(fd);
}

t_token	*find_delimiter_token(t_cmd *cmd, size_t *i, size_t *j)
{
	while (cmd[*i].token)
	{
		while (cmd[*i].token[*j].type)
		{
			if (cmd[*i].token[*j].type == T_REDIRECT
				&& ft_strcmp("<<", cmd[*i].token[*j].str) == 0)
				return (&(cmd[*i].token[++*j]));
			*j += 1;
		}
		*i += 1;
		*j = 0;
	}
	return (NULL);
}

void	heredoc_in_child_process(t_cmd *cmd)
{
	pid_t	pid;
	size_t	i;
	size_t	j;
	size_t	tmp_file_cnt;
	t_token	*delimiter_token;

	set_signal(HEREDOC);
	pid = fork();
	if (pid == 0)
	{
		i = 0;
		j = 0;
		tmp_file_cnt = 0;
		while (1)
		{
			delimiter_token = find_delimiter_token(cmd, &i, &j);
			if (delimiter_token == NULL)
				break ;
			heredoc_one(delimiter_token, tmp_file_cnt);
			tmp_file_cnt += 1;
		}
		exit(EXIT_SUCCESS);
	}
	set_signal(IGNORE);
}

int	wait_heredoc(void)
{
	int	status;

	status = 0;
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
	{
		printf("\n");
		g_errno = 1;
		return (1);
	}
	return (0);
}

int	heredoc(t_cmd *cmd)
{
	int	exit_code;

	heredoc_in_child_process(cmd);
	exit_code = wait_heredoc();
	set_signal(SHELL);
	if (exit_code == EXIT_SUCCESS)
		change_delimiter_to_file_name(cmd);
	return (exit_code);
}
