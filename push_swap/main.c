/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:10:40 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/28 13:05:47 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exit_with_err(const char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	exit(1);
}

void	init_deque(int argc, char **argv, t_data *data)
{
	int	idx;
	int	val;

	deque_init(&data->a);
	deque_init(&data->b);
	deque_init(&data->to_print);
	idx = 1;
	while (idx < argc)
	{
		val = ft_atoi(argv[idx]);
		if (deque_find_data(&data->a, val))
			exit_with_err("Error\n");
		deque_push_bottom(&data->a, val);
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

void	init(int argc, char **argv, t_data *data)
{
	int	*num_list;

	init_deque(argc, argv, data);
	if (is_deque_sorted(&data->a, data->a.size))
		exit(0);
	num_list = get_num_list(data->a.size, argv);
	quick_sort(num_list, 0, data->a.size - 1);
	num_list = set_idx_return_null(&data->a, num_list);
	data->is_first = 1;
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_argv(argc, argv);
	init(argc, argv, &data);
	if (data.a.size <= 5)
		sort_under_five(&data);
	else
		a_to_b(0, data.a.size, &data);
	optimize_result(&data.to_print);
	deque_print_result(&data.to_print);
}
