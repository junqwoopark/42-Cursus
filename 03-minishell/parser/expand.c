/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:35:33 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/04 16:25:02 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_tmp_expanded_str(char **tmp, char **expanded_str)
{
	char	*to_free;

	if (*expanded_str == NULL)
	{
		*expanded_str = ft_strdup(*tmp);
		free(*tmp);
		return (*expanded_str);
	}
	to_free = *expanded_str;
	*expanded_str = ft_strjoin(*expanded_str, *tmp);
	free(*tmp);
	free(to_free);
	return (*expanded_str);
}

char	*get_expanded_str(char *str, t_env *envp_copy)
{
	int		in_quote;
	char	*tmp;
	char	*expanded_str;

	expanded_str = NULL;
	in_quote = 0;
	while (*str)
	{
		tmp = NULL;
		if (*str == '$')
			tmp = get_env_expanded_str(&str, envp_copy, in_quote);
		else if (*str == '\"')
			skip_dquote_and_set_in_quote(&str, &in_quote);
		else if (*str == '\'' && !in_quote)
			tmp = get_squote_expanded_str(&str);
		else
			tmp = get_str_stop_at_quote_and_dollar(&str, in_quote);
		if (tmp)
			expanded_str = join_tmp_expanded_str(&tmp, &expanded_str);
	}
	return (expanded_str);
}
