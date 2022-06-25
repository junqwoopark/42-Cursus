/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:10:40 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/25 16:51:49 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exit_with_err(const char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
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
			exit_with_err("Error\n");
		deque_push_bottom(p_a, data);
		idx++;
	}
}

void	optimize_result(t_deque *result)
{
	t_node	*node;

	node = result->bottom;
	while (node && node->over)
	{
		if ((node->data == SA && node->over->data == SB)
			|| (node->data == SB && node->over->data == SA))
		{
			node->data = SS;
			deque_del(result, node->over);
		}
		else if ((node->data == RA && node->over->data == RB)
			|| (node->data == RB && node->over->data == RA))
		{
			node->data = RR;
			deque_del(result, node->over);
		}
		else if ((node->data == RRA && node->over->data == RRB)
			|| (node->data == RRB && node->over->data == RRA))
		{
			node->data = RRR;
			deque_del(result, node->over);
		}
		node = node->over;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		*num_list;

	check_argv(argc, argv);
	init_deque(argc, argv, &data.a, &data.b);
	if (is_deque_sorted(&data.a, data.a.size))
		return (0);
	deque_init(&data.to_print);
	num_list = get_num_list(data.a.size, argv);
	quick_sort(num_list, 0, data.a.size - 1);
	num_list = set_idx_return_null(&data.a, num_list);
	data.is_first = 1;
	if (data.a.size <= 5)
		sort_under_five(&data);
	else
		a_to_b(0, data.a.size, &data);
	optimize_result(&data.to_print);
	deque_print_result(&data.to_print);
}
