/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:51:09 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/09 23:00:23 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long long	ret;
	int			sign;

	ret = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			exit_with_error("ft_atoi : is not digit\n");
		ret = ret * 10 + *str - '0';
		if (ret < 0)
			exit_with_error("ft_atoi : overflow\n");
		str++;
	}
	return (ret * sign);
}


// void	usleep(long long u_sec)
// {
// 	long long	target_u_sec;

// 	target_u_sec = get_us_of_day() + u_sec;
// 	while (target_u_sec > get_us_of_day())
// 	{
// 		usleep(50);
// 	}
// }

long long	get_us_of_passed_time(long long start)
{
	return ((get_us_of_day() - start));
}

void	print_event(t_philo *philo, char *event)
{
	pthread_mutex_lock(philo->shared->event);
	printf("%lldms %d %s", get_us_of_passed_time(philo->shared->rule.time.start) / 1000, philo->tid, event);
	pthread_mutex_unlock(philo->shared->event);
}

