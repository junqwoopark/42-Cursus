/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:58:12 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/01 14:15:54 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_digit_only(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == 0)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	is_ft_atoi_overflow(const char *str)
{
	long long	ret;
	int			sign;

	ret = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		ret = ret * 10 + *str - '0';
		if (ret >= 2147483648 && sign == 1)
			return (1);
		else if (ret >= 2147483649)
			return (1);
		str++;
	}
	return (0);
}

void	check_argv(int argc, char **argv)
{
	int		idx;
	char	*tmp;

	if (argc == 1)
		exit(0);
	idx = 1;
	while (idx < argc)
	{
		tmp = ft_strtrim(argv[idx], "\f\r \t\v\n");
		if (!tmp)
			exit_with_err("Error\n");
		if (!is_digit_only(tmp) || is_ft_atoi_overflow(tmp))
			exit_with_err("Error\n");
		free(tmp);
		idx++;
	}
}
