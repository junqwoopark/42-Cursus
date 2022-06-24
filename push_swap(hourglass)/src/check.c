/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:58:12 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 20:59:20 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_digit_only(const char *str)
{
	if (*str == '-')
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

int	is_ft_atoi_overflow(const char *str)
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
	int	idx;

	if (argc == 1)
		exit_with_error("Error\n");
	idx = 1;
	while (idx < argc)
	{
		if (!is_digit_only(argv[idx]) || is_ft_atoi_overflow(argv[idx]))
			exit_with_error("Error\n");
		idx++;
	}
}
