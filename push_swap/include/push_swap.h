/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:33:07 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/07 19:35:33 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include "../lib/libft/libft.h"

# define TRUE 1
# define FALSE 0

typedef struct s_node
{
	int				data;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_deque
{
	int		size;
	t_node	*left;
	t_node	*right;
}	t_deque;

void	deque_init(t_deque **p_deque);
int		is_deque_empty(t_deque *p_deque);
int		deque_get_left(t_deque *p_deque);
int		deque_get_right(t_deque *p_deque);
int		deque_pop_left(t_deque *p_deque);
int		deque_pop_right(t_deque *p_deque);
void	deque_push_left(t_deque *p_deque, int data);
void	deque_push_right(t_deque *p_deque, int data);
t_node	*deque_find_data(t_deque *p_deque, int data);
void	deque_print_data(t_deque *p_deque);

#endif
