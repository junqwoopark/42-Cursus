/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:26:15 by chukim            #+#    #+#             */
/*   Updated: 2022/08/04 20:57:51 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errno;

void	print_simpson(void)
{
	int		fd;
	size_t	length;
	char	buff[500001];

	fd = open("simpson", O_RDONLY);
	length = read(fd, buff, 500000);
	write(1, buff, length);
	close(fd);
}

void	init_terminal(int argc, char **argv, char **envp, t_env **envp_copy)
{
	struct termios	term;

	(void) argv;
	if (argc != 1)
		exit_with_err("argument input error", NULL, 126, 1);
	print_simpson();
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SHELL);
	*envp_copy = copy_envp(envp);
}

void	print_exit(void)
{
	printf("\001\e[1A\002");
	printf("\001\e[12C\002");
	printf("exit\n");
}

void	run_input(char *input, t_env *envp_copy)
{
	t_cmd	*cmd;
	t_token	*token;
	char	**envp_copy_arr;

	token = parse(input, envp_copy);
	if (token)
	{
		envp_copy_arr = get_envp_copy_arr(envp_copy);
		cmd = get_cmd(token, envp_copy, envp_copy_arr);
		if (heredoc(cmd) == EXIT_SUCCESS)
			exec(cmd);
		unlink_all(cmd);
		free_cmd(&cmd);
		free_token(&token);
		free_envp_copy_arr(&envp_copy_arr);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*envp_copy;

	init_terminal(argc, argv, envp, &envp_copy);
	while (1)
	{
		input = readline("minishell $ ");
		if (input == NULL)
		{
			print_exit();
			break ;
		}
		else if (*input != '\0')
		{
			add_history(input);
			run_input(input, envp_copy);
		}
		free(input);
	}
	return (g_errno);
}
