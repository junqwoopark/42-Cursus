/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:32:59 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 13:05:39 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token_size(char *input, char *in_quote)
{
	size_t	i;
	size_t	ret;

	ret = 0;
	while (*input)
	{
		while (ft_isspace(*input))
		{
			input++;
			in_quote++;
		}
		i = 0;
		while (input[i]
			&& ((!ft_isspace(input[i]) && !in_quote[i]) || in_quote[i]))
			i++;
		if (i != 0)
		{
			input += i;
			in_quote += i;
			ret += 1;
		}
	}
	return (ret);
}

void	skip_space(char **input, char **in_quote)
{
	while (ft_isspace(**input))
	{
		(*input)++;
		(*in_quote)++;
	}
}

t_token	*get_token(char *input, char *in_quote)
{
	t_token	*token;
	size_t	i;
	size_t	j;

	j = 0;
	token = ft_calloc(sizeof(t_token), get_token_size(input, in_quote) + 1);
	while (*input)
	{
		skip_space(&input, &in_quote);
		i = 0;
		while (input[i]
			&& ((!ft_isspace(input[i]) && !in_quote[i]) || in_quote[i]))
			i++;
		if (i != 0)
		{
			token[j].str = ft_strndup(input, i);
			j++;
		}
		input += i;
		in_quote += i;
	}
	token[j].str = NULL;
	token[j].type = T_NULL;
	return (token);
}

t_token	*label_token(t_token *token)
{
	size_t	i;

	i = 0;
	while (token[i].str)
	{
		if (!ft_strcmp(token[i].str, "|"))
			token[i].type = T_PIPE;
		else if (!ft_strcmp(token[i].str, "<")
			|| !ft_strcmp(token[i].str, "<<")
			|| !ft_strcmp(token[i].str, ">")
			|| !ft_strcmp(token[i].str, ">>"))
			token[i].type = T_REDIRECT;
		else if (!ft_strcmp(token[i].str, "||")
			|| !ft_strcmp(token[i].str, "&&")
			|| !ft_strcmp(token[i].str, "&")
			|| !ft_strcmp(token[i].str, ";")
			|| !ft_strcmp(token[i].str, ";;"))
			token[i].type = T_ERROR;
		else
			token[i].type = T_WORD;
		i++;
	}
	return (token);
}

int	is_token_error(t_token *token)
{
	size_t	i;

	i = 0;
	while (token[i].str)
	{
		if (token[i].type == T_ERROR)
		{
			print_token_error(token[i].str);
			return (1);
		}
		i++;
	}
	return (0);
}
