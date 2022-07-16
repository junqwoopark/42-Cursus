/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:25:23 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/16 21:36:16 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

enum	e_check
{
	IS_END,
	IS_FULL,
	TIME_PASSED
};

typedef struct s_time
{
	time_t	die;
	time_t	eat;
	time_t	sleep;
	time_t	start;
}	t_time;

typedef struct s_number
{
	int	philosophers;
	int	must_eat;
}	t_number;

typedef struct s_observer
{
	int	nbr_of_full;
	int	is_end;
	int	is_error;
}	t_observer;

struct s_philo;

typedef struct s_shared
{
	t_time			time;
	t_number		number;
	t_observer		observer;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*event;
}	t_shared;

typedef struct s_philo
{
	int				tid;
	int				meal_cnt;
	time_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	t_shared		*shared;
}	t_philo;

typedef struct s_instance
{
	t_philo		*philos;
	t_shared	shared;
}	t_instance;

// utils.c
int					ft_atoi(const char *str);
time_t				get_ms_of_passed_time(time_t start);
void				print_mutex(t_philo *philo, char *print);
int					check_mutex(t_shared *shared, t_philo *philos, int to_check, int idx);

// init.c
void	init_instance(int argc, char **argv, t_instance *instance);

//philosophers.c
void	*routine(void *arg);
void	ft_usleep(time_t wait_time);

// init.c
time_t	get_ms_of_day(void);

// observing.c
void	observing(t_shared *shared, t_philo *philos);

#endif
