/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:10:40 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/02 17:41:21 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// void	parse_input(char **argv)
// {

// }

int	main(int argc, char **argv)
{
	t_deque	*a;
	t_deque	*b;

	deque_init(&a);
	deque_init(&b);
	deque_push_right(a, 3);
	printf("%d\n", deque_get_left(a));
}
