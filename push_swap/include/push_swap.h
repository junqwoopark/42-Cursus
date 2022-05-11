/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:33:07 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/10 14:31:32 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include "../lib/libft/libft.h"

# define TRUE 1
# define FALSE 0

enum e_cmd
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
};

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

void	deque_init(t_deque *p_deque);
int		is_deque_empty(t_deque *p_deque);
int		deque_get_size(t_deque *p_deque);
int		deque_get_left(t_deque *p_deque);
int		deque_get_right(t_deque *p_deque);
int		deque_pop_left(t_deque *p_deque);
int		deque_pop_right(t_deque *p_deque);
void	deque_push_left(t_deque *p_deque, int data);
void	deque_push_right(t_deque *p_deque, int data);
t_node	*deque_find_data(t_deque *p_deque, int data);
void	deque_print_data(t_deque *p_deque);
void	deque_print_char(t_deque *p_deque);
int		is_deque_sorted(t_deque *p_a);
int		deque_get_idx_to_top(t_deque *p_deque, int data);
void	quick_sort(int *input, int first, int last);

void	pa(t_deque *stack_a, t_deque *stack_b, t_deque *to_print);
void	pb(t_deque *stack_a, t_deque *stack_b, t_deque *to_print);
void	ra(t_deque *stack_a, t_deque *to_print);
void	rb(t_deque *stack_b, t_deque *to_print);
void	rr(t_deque *stack_a, t_deque *stack_b, t_deque *to_print);
void	rra(t_deque *stack_a, t_deque *to_print);
void	rrb(t_deque *stack_b, t_deque *to_print);
void	rrr(t_deque *stack_a, t_deque *stack_b, t_deque *to_print);
void	sa(t_deque *stack_a, t_deque *to_print);
void	sb(t_deque *stack_b, t_deque *to_print);
void	ss(t_deque *stack_a, t_deque *stack_b, t_deque *to_print);
#endif
