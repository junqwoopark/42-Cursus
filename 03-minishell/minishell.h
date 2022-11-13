/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:28:49 by chukim            #+#    #+#             */
/*   Updated: 2022/08/04 20:52:14 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include "libft/libft.h"

enum	e_types
{
	T_NULL,
	T_WORD,
	T_PIPE,
	T_REDIRECT,
	T_FILE,
	T_ERROR
};

enum	e_setsignal
{
	SHELL,
	HEREDOC,
	DEFAULT,
	IGNORE,
};

# define READ 0
# define WRITE 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*str;
	int				type;
}	t_token;

typedef struct s_cmd {
	int		argc;
	char	**argv;

	int		*read_pipe;
	int		*write_pipe;
	char	**envp_copy_arr;
	t_env	*envp_copy;
	t_token	*token;
}	t_cmd;

extern int	g_errno;

// ./heredoc/heredoc.c
int		heredoc(t_cmd *cmd);

// ./heredoc/heredoc_utils.c
void	change_delimiter_to_file_name(t_cmd *cmd);
char	*get_tmp_file_path(size_t tmp_file_cnt);
void	clear_file(int fd, char *tmp_file_path, size_t tmp_file_cnt);

// ./heredoc/unlink.c
void	unlink_all(t_cmd *cmd);

// free.c
void	free_token(t_token **token);
void	free_envp_copy_arr(char ***envp_copy_arr);
void	free_cmd(t_cmd **cmd);
void	free_env_path(char ***envp_path);

// ./parser/parse.c
t_token	*parse(char *input, t_env *envp_copy);

// ./parser/parse_utils.c
int		is_valid_quote(char *input);
void	init_in_quote(char *input, char *in_quote);
char	*get_env_return_null(t_env *envp_copy, char *key);

// ./parser/token_utils.c
size_t	get_token_size(char *input, char *is_in_quote);
t_token	*get_token(char *input, char *is_in_quote);
t_token	*label_token(t_token *token);
int		is_token_error(t_token *token);

// ./parser/expand_utils.c
char	*get_env_with_find_key(char **str, t_env *envp_copy, int in_quote);
char	*get_env_expanded_str(char **str, t_env *envp_copy, int in_quote);
char	*get_squote_expanded_str(char **str);
char	*get_str_stop_at_quote_and_dollar(char **str, int in_quote);
void	skip_dquote_and_set_in_quote(char **str, int *in_quote);

// ./parser/expand.c
char	*get_expanded_str(char *str, t_env *envp_copy);

// ./parser/big_utils.c
void	init_big(char *input, char *in_quote,
			char *big_input, char *big_in_quote);

// print.c
void	print_str_arr(char *argv[]);
void	print_export(t_cmd *cmd);

// ./env/env.c
char	**get_envp_copy_arr(t_env *envp_copy);
char	*get_env(t_env *envp_copy, char *key);
t_env	*env_new(void);

// ./env/env_utils.c
char	**divide_with_equal(char *str);
void	add_env(t_env *envp_copy, char *key, char *value);
t_env	*copy_envp(char *envp[]);

// ./cmd/cmd.c
t_cmd	*get_cmd(t_token *token, t_env *envp_copy, char **envp_copy_arr);
void	add_or_update_env(char *str, t_env *envp);

// ./cmd/cmd_utils.c
size_t	get_cnt_of_pipe(t_token *token);

// ./utils/error.c
void	exit_with_err(char *str1, char *str2, int exit_code, int to_exit);
void	exit_with_err_second(char *str1, char *str2, char *str3, int exit_code);
void	print_err(char *s1, char *s2, char *s3);
void	print_token_error(char *error_token);
int		return_with_err(char *str1, char *str2, char *str3, int exit_code);

// exec.c
void	exec(t_cmd *cmd);
// ./exec/exec_utils.c
size_t	get_cnt_of_cmd(t_cmd *cmd);
// ./exec/exec_wait.c
void	wait_child_process(pid_t pid);
// ./exec/path_utils.c
char	**get_env_path(char *envp[]);
int		is_cmd_contain_slash(t_cmd *cmd);
char	*get_cmd_path(char *path[], t_cmd *cmd);
// ./exec/pipe_utils.c
void	init_pipe(int *read_pipe, int *write_pipe);
void	update_pipe(int *read_pipe, int *write_pipe, int i, int cnt_of_cmd);
// ./exec/redirect_utils.c
int		redirect_in(t_cmd *cmd);
int		redirect_out(t_cmd *cmd);
// ./exec/run_utils.c
int		is_builtin(t_cmd *cmd);
void	run_builtin(t_cmd *cmd);
void	run_cmd(t_cmd *cmd);
// ./exec/file_utils.c
void	ft_close(int fd);
void	ft_dup2(int fd1, int fd2);
int		is_excutable(char *path);

// signal.c
void	set_signal(int type);

// export.c
void	ft_export(t_cmd *cmd);

// export_utils.c
size_t	get_envp_copy_size_with_null(t_env *envp_copy);
char	**set_envp_copy_arr_with_null(char **envp_copy_arr, t_env *envp_copy);
char	**get_envp_copy_arr_with_null(t_env *envp_copy);

// unset.c
void	ft_unset(t_cmd *cmd);

// env.c
void	ft_env(t_cmd *cmd);

// pwd.c
void	ft_pwd(t_cmd *cmd);

// echo.c
void	ft_echo(t_cmd *cmd);

// cd.c
void	ft_cd(t_cmd *cmd);

// exit.c
void	ft_exit(t_cmd *cmd);
void	ft_exit_multiple_cmd(t_cmd *cmd);

#endif
