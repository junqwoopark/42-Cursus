/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:15:37 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/30 17:09:30 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(int *x, int *y)
{
	int	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void	quick_sort(int *input, int first, int last)
{
	int	pivot;
	int	i;
	int	j;

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
				swap(&input[i], &input[j]);
		}
		swap(&input[pivot], &input[j]);
		quick_sort(input, first, j - 1);
		quick_sort(input, j + 1, last);
	}
}
