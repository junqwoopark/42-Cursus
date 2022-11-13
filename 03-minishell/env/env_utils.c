/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:05:49 by chukim            #+#    #+#             */
/*   Updated: 2022/08/03 17:16:08 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**divide_with_equal2(int i, char *str, char **ret)
{
	int	j;
	int	k;

	ret[0] = ft_calloc(i + 1, sizeof(char));
	j = -1;
	while (++j < i)
		ret[0][j] = str[j];
	if (ft_strlen(str) - i == 0)
	{
		ret[1] = NULL;
		return (ret);
	}
	k = 0;
	ret[1] = ft_calloc(ft_strlen(str) - i, sizeof(char));
	while (str[j + 1] != '\0')
	{
		ret[1][k] = str[j + 1];
		j++;
		k++;
	}
	return (ret);
}

char	**divide_with_equal(char *str)
{
	int		i;
	char	**ret;

	i = 0;
	ret = ft_calloc(2, sizeof(char *));
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (divide_with_equal2(i, str, ret));
}

void	add_env(t_env *envp_copy, char *key, char *value)
{
	t_env	*current;

	current = envp_copy;
	while (current->next != NULL)
		current = current->next;
	current->key = key;
	current->value = value;
	current->next = env_new();
}

t_env	*copy_envp(char *envp[])
{
	int		i;
	char	**ret;
	t_env	*envp_copy;

	envp_copy = env_new();
	i = 0;
	while (envp[i] != NULL)
	{
		ret = divide_with_equal(envp[i]);
		add_env(envp_copy, ret[0], ret[1]);
		free(ret);
		i++;
	}
	return (envp_copy);
}
