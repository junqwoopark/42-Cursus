/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:10:40 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/01 10:34:26 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void exit_with_err(const char *err) {
  ft_putstr_fd(err, 2);
  exit(1);
}

void free_deques(t_data *data) {
  deque_clear(&data->a);
  deque_clear(&data->b);
  deque_clear(&data->result);
}

int main(int argc, char **argv) {
  t_data data;

  check_argv(argc, argv);
  init_data(argc, argv, &data);
  if (!is_deque_sorted(&data.a, data.a.size)) {
    if (data.a.size <= 5)
      sort_under_five(&data, data.a.size);
    else
      a_to_b(0, data.a.size, &data);
  }
  optimize_result(&data.result);
  print_result(&data.result);
  free_deques(&data);
  return (0);
}
