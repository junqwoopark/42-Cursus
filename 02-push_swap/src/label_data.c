/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:36:06 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/30 16:54:33 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*get_num_list(int size, char **argv)
{
	int	*ret;
	int	idx;

	ret = malloc(sizeof(int) * size);
	if (ret == NULL)
		exit_with_err("Error\n");
	idx = 0;
	while (idx < size)
	{
		ret[idx] = ft_atoi(argv[idx + 1]);
		idx++;
	}
	return (ret);
}

static void	set_label(t_deque *a, int *num_list)
{
	int		idx;
	int		**val_addr;
	t_node	*node;

	idx = 0;
	val_addr = malloc(sizeof(int *) * a->size);
	if (val_addr == NULL)
		exit_with_err("Error\n");
	while (idx < a->size)
	{
		node = deque_find_node(a, num_list[idx]);
		val_addr[idx] = &(node->data);
		idx++;
	}
	idx = 0;
	while (idx < a->size)
	{
		*(val_addr[idx]) = idx;
		idx++;
	}
	free(val_addr);
}

void	label_data(char **argv, t_data *data)
{
	int	*num_list;

	num_list = get_num_list(data->a.size, argv);
	quick_sort(num_list, 0, data->a.size - 1);
	set_label(&data->a, num_list);
	free(num_list);
}
