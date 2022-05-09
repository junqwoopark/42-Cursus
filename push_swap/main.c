/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:10:40 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/09 15:53:05 by junkpark         ###   ########.fr       */
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

void	init_deque(int argc, char **argv, t_deque *p_a, t_deque *p_b)
{
	int	idx;
	int	data;

	deque_init(p_a);
	deque_init(p_b);
	idx = 1;
	while (idx < argc)
	{
		data = ft_atoi(argv[idx]);
		if (deque_find_data(p_a, data))
			exit_with_error("Error\n");
		deque_push_right(p_a, data);
		idx++;
	}
}

int	*get_num_list(int size, char **argv)
{
	int	*ret;
	int	idx;

	ret = malloc(sizeof(int) * size);
	if (ret == NULL)
		exit_with_error("Error\n");
	idx = 0;
	while (idx < size)
	{
		ret[idx] = ft_atoi(argv[idx + 1]);
		idx++;
	}
	return (ret);
}

int	*set_idx_return_null(t_deque *a, int *num_list)
{
	int		idx;
	t_node	*node;

	idx = 0;
	while (idx < a->size)
	{
		node = deque_find_data(a, num_list[idx]);
		node->data = idx;
		idx++;
	}
	free(num_list);
	return (NULL);
}

void	a_to_b(t_deque *p_a, t_deque *p_b, t_deque *to_print)
{
	int	num;
	int	top;
	int	chunk;

	chunk = 0.000000053 * (p_a->size) * (p_a->size) + 0.03 * (p_a->size) + 14.5;
	num = 0;
	while (p_a->size != 0)
	{
		top = deque_get_right(p_a);
		if (top <= num)
		{
			pb(p_a, p_b, to_print);
			num++;
		}
		else if (num < top && top <= num + chunk)
		{
			pb(p_a, p_b, to_print);
			rb(p_b, to_print);
			num++;
		}
		else if (num + chunk < top)
			ra(p_a, to_print);
	}
}

int	main(int argc, char **argv)
{
	t_deque	a;
	t_deque	b;
	int		*num_list;
	t_deque	to_print;

	check_argv(argc, argv);
	init_deque(argc, argv, &a, &b);
	num_list = get_num_list(a.size, argv);
	quick_sort(num_list, 0, a.size - 1);
	num_list = set_idx_return_null(&a, num_list);
}
