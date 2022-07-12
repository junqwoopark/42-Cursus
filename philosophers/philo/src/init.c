          /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:09:58 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/04 13:38:18 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_us_of_day(void)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL))
		exit_with_error("ERROR: gettimeofday()\n");
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	init_rule(int argc, char **argv, t_rule *rule)
{
	rule->is_ready = 0;
	rule->number.philosophers = ft_atoi(argv[1]);
	rule->time.die = ft_atoi(argv[2]) * 1000;
	rule->time.eat = ft_atoi(argv[3]) * 1000;
	rule->time.sleep = ft_atoi(argv[4]) * 1000;
	rule->time.start = get_us_of_day();
	if (argc == 6)
		rule->number.must_eat = ft_atoi(argv[5]);
	else
		rule->number.must_eat = -1;
}

void	init_forks(t_instance *instance)
{
	int				idx;

	instance->shared.forks = malloc(sizeof(pthread_mutex_t) * instance->shared.rule.number.philosophers);
	if (instance->shared.forks == NULL)
		exit_with_error("Error: malloc()\n");
	idx = 0;
	while (idx < instance->shared.rule.number.philosophers)
	{
		if (pthread_mutex_init(&instance->shared.forks[idx], NULL) != 0)
			exit_with_error("Error: pthread_mutex_init()\n");
		idx++;
	}
}

void	init_philos(t_instance *instance)
{
	int	idx;

	instance->philos = malloc(sizeof(t_philo) * instance->shared.rule.number.philosophers);
	if (instance->philos == NULL)
		exit_with_error("ERROR: malloc()\n");
	idx = 0;
	while (idx < instance->shared.rule.number.philosophers)
	{
		instance->philos[idx].tid = idx;
		instance->philos[idx].meal_cnt = 0;
		instance->philos[idx].lfork = &instance->shared.forks[idx];
		instance->philos[idx].rfork = &instance->shared.forks[(idx + instance->shared.rule.number.philosophers - 1) % instance->shared.rule.number.philosophers];
		instance->philos[idx].rule = &instance->shared.rule;
		instance->philos[idx].shared = &instance->shared;
		if (pthread_create(&instance->philos[idx].thread, NULL, routine, &instance->philos[idx]))
			exit_with_error("ERROR: pthread_create()\n");
		idx++;
	}
	idx = 0;
	while (idx < instance->shared.rule.number.philosophers)
	{
		pthread_detach(instance->philos[idx].thread);
		idx++;
	}
}

void	*monitoring(void *arg)
{
	int			idx;
	int			cnt;
	long long	time;
	t_instance		*instance;

	instance = arg;
	while (instance->shared.rule.is_ready == 0)
	{
	}
	ft_usleep(5000);
	while (1)
	{
		idx = 0;
		while (idx < instance->philos->rule->number.philosophers)
		{
			time = get_us_of_day();
			if (time - instance->philos[idx].last_meal > instance->philos[idx].rule->time.die)
			{
				print_event(&instance->philos[idx], "is died\n");
				exit(0);
			}
			idx++;
		}
		idx = 0;
		cnt = 0;
		while (idx < instance->philos->rule->number.philosophers)
		{
			if (instance->shared.rule.number.must_eat != -1 && instance->philos[idx].meal_cnt >= instance->shared.rule.number.must_eat)
				cnt++;
			idx++;
		}
		if (cnt == instance->shared.rule.number.philosophers)
			exit(0);
	}
	ft_usleep(5000);
}

void	init_monitor(t_instance *instance)
{
	instance->monitor = malloc(sizeof(pthread_t));
	if (pthread_create(instance->monitor, NULL, monitoring, instance) != 0)
		exit_with_error("ERROR: pthread_create()\n");
}

void	init_event(t_instance *instance)
{
	instance->shared.event = malloc(sizeof(pthread_mutex_t));
	if (instance->shared.event == NULL)
		exit_with_error("Error: malloc()\n");
	if (pthread_mutex_init(instance->shared.event, NULL) != 0)
		exit_with_error("Error: pthread_mutex_init()\n");
}

void	init_instance(int argc, char **argv, t_instance *instance)
{
	if (!(argc == 5 || argc == 6))
		exit_with_error("./philo number.philosophers time._die time._eat time._sleep [number.must_eat]");
	init_rule(argc, argv, &instance->shared.rule);
	init_forks(instance);
	init_event(instance);
	init_philos(instance);
	init_monitor(instance);
}
