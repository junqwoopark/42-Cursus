/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:21:41 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 18:21:46 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_envp_copy_size_with_null(t_env *envp_copy)
{
	size_t	size;
	t_env	*current;

	size = 0;
	current = envp_copy;
	while (current->next)
	{
		size++;
		current = current->next;
	}
	return (size);
}

char	**set_envp_copy_arr_with_null(char **envp_copy_arr, t_env *envp_copy)
{
	size_t	i;
	size_t	len;
	t_env	*current;

	current = envp_copy;
	i = 0;
	while (current->next)
	{
		len = ft_strlen(current->key) + ft_strlen(current->value);
		envp_copy_arr[i] = ft_calloc(len + 2, sizeof(char *));
		ft_strlcat(envp_copy_arr[i], current->key, len + 2);
		if (current->value != NULL)
		{
			ft_strlcat(envp_copy_arr[i], "=", len + 2);
			ft_strlcat(envp_copy_arr[i], current->value, len + 2);
		}
		i++;
		current = current->next;
	}
	return (envp_copy_arr);
}

char	**get_envp_copy_arr_with_null(t_env *envp_copy)
{
	size_t	envp_copy_size;
	char	**envp_copy_arr;

	envp_copy_size = get_envp_copy_size_with_null(envp_copy);
	envp_copy_arr = ft_calloc(envp_copy_size + 1, sizeof(char *));
	envp_copy_arr = set_envp_copy_arr_with_null(envp_copy_arr, envp_copy);
	return (envp_copy_arr);
}
