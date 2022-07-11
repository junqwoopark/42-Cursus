/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:25:23 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/09 23:00:16 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_time
{
	long long	die;
	long long	eat;
	long long	sleep;
	long long	start;
}	t_time;

typedef struct s_number
{
	int	philosophers;
	int	must_eat;
}	t_number;

typedef struct s_rule
{
	int			is_ready;
	t_time		time;
	t_number	number;
}	t_rule;

typedef struct s_shared
{
	t_rule			rule;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*event;
}	t_shared;

typedef struct s_philo
{
	int				tid;
	int				meal_cnt;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	t_rule			*rule;
	t_shared		*shared;
}	t_philo;

typedef struct s_instance
{
	t_shared		shared;
	t_philo			*philos;
	pthread_t		*monitor;
}	t_instance;

// main.c
void	exit_with_error(char *err);

// utils.c
int		ft_atoi(const char *str);
// void	usleep(long long u_sec);
long long	get_us_of_passed_time(long long start);
void	print_event(t_philo *philo, char *event);

// init.c
void	init_instance(int argc, char **argv, t_instance *instance);

//philosophers.c
void	*routine(void *arg);

// init.c
long long	get_us_of_day(void);

#endif
