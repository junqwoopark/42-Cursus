/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:01:30 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/24 21:54:33 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "../lib/libft/libft.h"
# include "../lib/libgnl/get_next_line.h"

typedef struct s_info
{
	int	idx;
	int	c;
}	t_info;

void	exit_with_err(char *err_msg);
void	print_pid();

#endif
