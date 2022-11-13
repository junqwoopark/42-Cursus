/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:43:54 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 13:04:06 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_space_near_special_character(
		char **input, char **in_quote, char **big_input, char **big_in_quote)
{
	**big_input = ' ';
	*big_input += 1;
	*big_in_quote += 1;
	**big_input = **input;
	if (*(*input + 1) == *(*input))
	{
		*input += 1;
		*in_quote += 1;
		*big_input += 1;
		*big_in_quote += 1;
		**big_input = **input;
	}
	*big_input += 1;
	*big_in_quote += 1;
	**big_input = ' ';
}

void	init_big(char *input, char *in_quote,
		char *big_input, char *big_in_quote)
{
	while (*input)
	{
		if (*in_quote)
		{
			*big_input = *input;
			*big_in_quote = *in_quote;
		}
		else
		{
			if (*input == '>' || *input == '<' || *input == '|'
				|| *input == ';' || *input == '&')
				insert_space_near_special_character(
					&input, &in_quote, &big_input, &big_in_quote);
			else
				*big_input = *input;
		}
		input += 1;
		in_quote += 1;
		big_input += 1;
		big_in_quote += 1;
		*big_input = '\0';
	}
}
