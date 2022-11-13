/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:25:23 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/20 19:30:24 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

enum	e_options
{
	IS_END,
	IS_FULL,
	DIED,
	EVENT
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

struct	s_philo;

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

// forks.c
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);

// init.c
void	init_instance(int argc, char **argv, t_instance *instance);

// philosophers.c
void	*routine(void *arg);

// simulate.c
void	simulate_solo(t_instance *instance);
void	simulate_philosophers(t_instance *instance);

// utils.c
int		ft_atoi(const char *str);
time_t	get_ms_of_day(void);
time_t	get_ms_of_passed_time(time_t start);
void	ft_msleep(time_t wait_time);

// atomic.c
void	print_atomic(t_philo *philo, char *print);
int		check_atomic(t_shared *shared, int to_check);

// observing.c
void	observing(t_shared *shared, t_philo *philos);

#endif
