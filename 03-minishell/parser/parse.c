/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:31:28 by chukim            #+#    #+#             */
/*   Updated: 2022/08/04 16:52:32 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexcial_analysis(char *input, char *in_quote)
{
	t_token	*token;

	token = get_token(input, in_quote);
	token = label_token(token);
	return (token);
}

t_token	*expand_token(t_token *token, t_env *envp_copy)
{
	size_t	i;
	char	*expanded_str;

	i = 0;
	while (token[i].str)
	{
		expanded_str = get_expanded_str(token[i].str, envp_copy);
		free(token[i].str);
		token[i].str = expanded_str;
		i++;
	}
	return (token);
}

t_token	*syntax_analysis(t_token *token)
{
	size_t	i;

	i = 0;
	while (token[i].type)
	{
		if (token[i].type == T_PIPE)
		{
			if (token[i + 1].type != T_WORD
				&& token[i + 1].type != T_REDIRECT)
				token[i].type = T_ERROR;
		}
		else if (token[i].type == T_REDIRECT)
		{
			if (token[i + 1].type != T_WORD)
				token[i].type = T_ERROR;
			else if (token[i + 1].type != T_NULL)
				token[i + 1].type = T_FILE;
		}
		i++;
	}
	return (token);
}

t_token	*trim_token(t_token *token, size_t token_size)
{
	size_t	i;

	while (token_size--)
	{
		i = 0;
		while (token[i].type)
		{
			if (token[i].str == NULL)
			{
				token[i].str = token[i + 1].str;
				token[i].type = token[i + 1].type;
				token[i + 1].str = NULL;
				if (token[i + 1].type != T_NULL)
					token[i + 1].type = T_WORD;
			}
			i++;
		}
	}
	return (token);
}

t_token	*parse(char *input, t_env *envp_copy)
{
	char	*in_quote;
	char	*big_input;
	char	*big_in_quote;
	t_token	*token;

	if (!is_valid_quote(input))
		return (NULL);
	in_quote = ft_calloc(ft_strlen(input) + 1, 1);
	big_input = ft_calloc(ft_strlen(input) * 3 + 1, 1);
	big_in_quote = ft_calloc(ft_strlen(input) * 3 + 1, 1);
	init_in_quote(input, in_quote);
	init_big(input, in_quote, big_input, big_in_quote);
	token = lexcial_analysis(big_input, big_in_quote);
	token = expand_token(token, envp_copy);
	token = syntax_analysis(token);
	token = trim_token(token, get_token_size(big_input, big_in_quote));
	if (is_token_error(token))
	{
		free_token(&token);
		token = NULL;
	}
	free(big_in_quote);
	free(big_input);
	free(in_quote);
	return (token);
}
