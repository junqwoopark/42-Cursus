/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:24:08 by chukim            #+#    #+#             */
/*   Updated: 2022/08/04 17:06:54 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_quote(char *input)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (*input)
	{
		if (*input == '\'' && (squote == 0 && dquote == 0))
			squote = 1;
		else if (*input == '\"' && (squote == 0 && dquote == 0))
			dquote = 1;
		else if (*input == '\'' && squote == 1)
			squote = 0;
		else if (*input == '\"' && dquote == 1)
			dquote = 0;
		input++;
	}
	if (squote == 1)
		print_token_error("'");
	else if (dquote == 1)
		print_token_error("\"");
	else
		return (1);
	return (0);
}

void	marking_in_quote(char *input, char *in_quote, int *squote, int *dquote)
{
	if (*input == '\'' && (*squote == 0 && *dquote == 0))
	{
		*squote = 1;
		*in_quote = 1;
	}
	else if (*input == '\"' && (*squote == 0 && *dquote == 0))
	{
		*dquote = 1;
		*in_quote = 2;
	}
	else if (*input == '\'' && *squote == 1)
	{
		*squote = 0;
		*in_quote = 1;
	}
	else if (*input == '\"' && *dquote == 1)
	{
		*dquote = 0;
		*in_quote = 2;
	}
	else if (*squote == 1)
		*in_quote = 1;
	else if (*dquote == 1)
		*in_quote = 2;
}

void	init_in_quote(char *input, char *in_quote)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (*input)
	{
		marking_in_quote(input, in_quote, &squote, &dquote);
		input++;
		in_quote++;
	}
}

char	*get_env_return_null(t_env *envp_copy, char *key)
{
	t_env	*current;

	current = envp_copy;
	while (current->next != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->value != NULL)
				return (current->value);
			else
				return ("");
		}
		current = current -> next;
	}
	return (NULL);
}
