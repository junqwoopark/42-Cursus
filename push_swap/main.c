/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:10:40 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/07 19:45:27 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exit_with_error(const char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	exit(1);
}

int	is_digit_only(const char *str)
{
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

void	init_deque(int argc, char **argv, t_deque **p_a, t_deque **p_b)
{
	int	idx;
	int	data;

	deque_init(p_a);
	deque_init(p_b);
	idx = 1;
	while (idx < argc)
	{
		data = ft_atoi(argv[idx]);
		if (deque_find_data(*p_a, data))
			exit_with_error("Error\n");
		deque_push_right(*p_a, data);
		idx++;
	}
}

int	main(int argc, char **argv)
{
	t_deque	*a;
	t_deque	*b;

	check_argv(argc, argv);
	init_deque(argc, argv, &a, &b);
}
