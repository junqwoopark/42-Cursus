/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:10:40 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 21:00:20 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exit_with_error(const char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	exit(1);
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
		deque_push_left(p_a, data);
		idx++;
	}
}

int	main(int argc, char **argv)
{
	t_deque	a;
	t_deque	b;
	t_deque	to_print;
	int		*num_list;

	check_argv(argc, argv);
	init_deque(argc, argv, &a, &b);
	if (is_deque_sorted(&a))
		return (0);
	deque_init(&to_print);
	num_list = get_num_list(a.size, argv);
	quick_sort(num_list, 0, a.size - 1);
	num_list = set_idx_return_null(&a, num_list);
	if (a.size <= 5)
	{
		sort_under_five(&a, &b, &to_print);
		deque_print_result(&to_print);
		return (0);
	}
	a_to_b(&a, &b, &to_print);
	b_to_a(&a, &b, &to_print);
	deque_print_result(&to_print);
}
