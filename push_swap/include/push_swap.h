/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:33:07 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/25 16:57:25 by junkpark         ###   ########.fr       */
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
	struct s_node	*over;
	struct s_node	*under;
}	t_node;

typedef struct s_deque
{
	int		size;
	t_node	*bottom;
	t_node	*top;
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
	t_deque		to_print;
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

// deque_utils.c
void	deque_init(t_deque *p_deque);
int		is_deque_empty(t_deque *p_deque);
int		is_deque_sorted(t_deque *deque, int size);
int		is_deque_sorted_reversed(t_deque *deque, int size);

// deque_del.c
void	deque_del(t_deque *deque, t_node *node);

// deque_push.c
void	deque_push_bottom(t_deque *p_deque, int data);
void	deque_push_top(t_deque *p_deque, int data);

// deque_pop.c
int		deque_pop_bottom(t_deque *p_deque);
int		deque_pop_top(t_deque *p_deque);

// deque_get.c
int		deque_get_size(t_deque *p_deque);
int		deque_get_bottom(t_deque *p_deque);
int		deque_get_top(t_deque *p_deque);
int		deque_get_max(t_deque *p_deque, int size);
int		deque_get_min(t_deque *p_deque, int size);

//deque_find_print.c
t_node	*deque_find_data(t_deque *p_deque, int data);
void	deque_print_data(t_deque *p_deque);
void	deque_print_result(t_deque *p_deque);
int		deque_get_idx(t_deque *p_deque, int data);

// check.c
int		is_digit_only(const char *str);
int		is_ft_atoi_overflow(const char *str);
void	check_argv(int argc, char **argv);

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
void	to_avoid_norminette(int *input, int *temp, int pivot, int j);
void	quick_sort(int *input, int first, int last);
int		*get_num_list(int size, char **argv);
int		*set_idx_return_null(t_deque *a, int *num_list);

// swap.c
void	a_to_b(int start, int size, t_data *data);
void	b_to_a(int start, int size, t_data *data);

// reverse.c
void	init_instance(t_instance *instance, int start, int size);
void	reverse(int ra_cnt, int rb_cnt, t_data *data);

// a_to_b.c
void	a_to_b(int start, int size, t_data *data);

// b_to_a.c
void	b_to_a(int start, int size, t_data *data);

// sort_under_five.c
void	sort_two(t_data *data);
void	sort_three(t_data *data);
void	sort_four(t_data *data);
void	sort_five(t_data *data);
void	sort_under_five(t_data *data);

// sort_under_three.c
void	sort_under_three(t_data *data, int size);

// main.c
void	exit_with_err(const char *error_msg);
void	init_deque(int argc, char **argv, t_deque *p_a, t_deque *p_b);

#endif
