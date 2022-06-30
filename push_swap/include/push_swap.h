/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:33:07 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/30 17:10:07 by junkpark         ###   ########.fr       */
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
	t_node	*front;
	t_node	*back;
}	t_deque;

typedef struct s_pivots
{
	int	min;
	int	max;
}	t_pivots;

typedef struct s_data
{
	t_deque		a;
	t_deque		b;
	t_deque		result;
	int			is_first;
}	t_data;

typedef struct s_instance
{
	int			ra_cnt;
	int			rb_cnt;
	int			pa_cnt;
	int			pb_cnt;
	int			size;
	t_pivots	pivots;
}	t_instance;

// main.c
void	exit_with_err(const char *err_msg);

// a_to_b.c
void	a_to_b(int start, int size, t_data *data);

// b_to_a.c
void	b_to_a(int start, int size, t_data *data);

// check.c
void	check_argv(int argc, char **argv);

// deque_del.c
void	deque_del(t_deque *deque, t_node *node);

// deque_find_print.c
t_node	*deque_find_node(t_deque *p_deque, int data);
void	deque_print_data(t_deque *p_deque);
int		deque_find_idx(t_deque *p_deque, int data);

// deque_get.c
int		deque_get_size(t_deque *p_deque);
int		deque_get_front(t_deque *p_deque);
int		deque_get_back(t_deque *p_deque);
int		deque_get_max(t_deque *p_deque, int size);
int		deque_get_min(t_deque *p_deque, int size);

// deque_pop.c
int		deque_pop_front(t_deque *p_deque);
int		deque_pop_back(t_deque *p_deque);

// deque_push.c
void	deque_push_front(t_deque *p_deque, int data);
void	deque_push_back(t_deque *p_deque, int data);

// deque_utils.c
void	deque_init(t_deque *p_deque);
int		is_deque_empty(t_deque *p_deque);
int		is_deque_sorted(t_deque *deque, int size);
int		is_deque_sorted_reversed(t_deque *deque, int size);

// init.c
void	init_data(int argc, char **argv, t_data *data);
void	init_instance(t_instance *instance, int start, int size);

// label_data.c
void	label_data(char **argv, t_data *data);

// push_swap_p.c
void	pa(t_data *data);
void	pb(t_data *data);

// push_swap_r.c
void	ra(t_data *data);
void	rb(t_data *data);
void	rr(t_data *data);

// push_swap_rr.c
void	rra(t_data *data);
void	rrb(t_data *data);
void	rrr(t_data *data);

// push_swap_s.c
void	sa(t_data *data);
void	sb(t_data *data);
void	ss(t_data *data);

// quick_sort.c
void	quick_sort(int *input, int first, int last);

// result.c
void	optimize_result(t_deque *result);
void	print_result(t_deque *result);

// reverse.c
void	reverse(int ra_cnt, int rb_cnt, t_data *data);

// sort_three_while_recursive.c
void	sort_three_while_recursive(t_data *data);

// sort_under_five.c
void	sort_under_five(t_data *data, int size);

#endif
