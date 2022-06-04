/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:25:23 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/02 14:54:19 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_info;

typedef	struct s_instance
{
	pthread_mutex_t	*forks;
	pthread_t		*philosophers;
	t_info	info;
}	t_instance;


// main.c
void	exit_with_error(char *err);

// utils.c
int		ft_atoi(const char *str);

// init.c
void	init_instance(int argc, char **argv, t_instance *instance);
#endif
