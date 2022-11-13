/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:27:44 by chukim            #+#    #+#             */
/*   Updated: 2022/08/03 19:37:54 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_end(char c, int flag)
{
	if (c == '=' && flag == 0)
		printf("\"\"");
	if (flag == 1)
		printf("\"\n");
	else
		printf("\n");
}

int	compare_str(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] - str2[i] < 0)
			return (1);
		else if (str1[i] - str2[i] > 0)
			return (0);
		i++;
	}
	if (str1[i] == '\0')
		return (1);
	else
		return (0);
}

void	print_str_arr(char *argv[])
{
	size_t	i;
	size_t	j;
	int		flag;

	i = 0;
	flag = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		printf("declare -x ");
		while (argv[i][j] != '\0')
		{
			if (argv[i][j - 1] == '=' && flag != 1)
			{
				printf("\"");
				flag = 1;
			}
			printf("%c", argv[i][j]);
			j++;
		}
		print_end(argv[i][j - 1], flag);
		flag = 0;
		i++;
	}
}

void	print_export(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	char	*temp;
	char	**tmp;

	tmp = \
		get_envp_copy_arr_with_null(cmd->envp_copy);
	i = 0;
	while (tmp[i] != NULL)
	{
		j = i + 1;
		while (tmp[j] != NULL)
		{
			if (compare_str(tmp[i], tmp[j]) == 0)
			{
				temp = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = temp;
			}
			j++;
		}
		i++;
	}
	print_str_arr(tmp);
	free_envp_copy_arr(&tmp);
}
