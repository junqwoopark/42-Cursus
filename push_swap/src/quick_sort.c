/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:15:37 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/28 12:54:42 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	to_avoid_norminette(int *input, int *temp, int pivot, int j)
{
	*temp = input[pivot];
	input[pivot] = input[j];
	input[j] = *temp;
}

void	quick_sort(int *input, int first, int last)
{
	int	pivot;
	int	i;
	int	j;
	int	temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;
		while (i < j)
		{
			while (input[i] <= input[pivot] && i < last)
				i++;
			while (input[j] > input[pivot])
				j--;
			if (i < j)
				to_avoid_norminette(input, &temp, i, j);
		}
		to_avoid_norminette(input, &temp, pivot, j);
		quick_sort(input, first, j - 1);
		quick_sort(input, j + 1, last);
	}
}

int	*get_num_list(int size, char **argv)
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

int	*set_idx_return_null(t_deque *a, int *num_list)
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
		node = deque_find_data(a, num_list[idx]);
		val_addr[idx] = &(node->data);
		idx++;
	}
	idx = 0;
	while (idx < a->size)
	{
		*(val_addr[idx]) = idx;
		idx++;
	}
	free(num_list);
	free(val_addr);
	return (NULL);
}
