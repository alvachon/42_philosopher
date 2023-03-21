/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:55:10 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/21 16:23:38 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
Actual time in MS (Miliseconds)
Converting time in miliseconds:
Seconds needs to be mutlplied by 1000;
Microseconds need to be divided by 1000;*/
long int	actual_time(void)
{
	long int		time;
	long int		seconds;
	long int		microseconds;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	seconds = (current_time.tv_sec * 1000);
	microseconds = (current_time.tv_usec / 1000);
	time = seconds + microseconds;
	return (time);
}

void	ms_wait(long int limit)
{
	long int	now;
	long int	timer;

	now = actual_time();
	timer = (actual_time() - now);
	while (timer < limit)
	{
		timer = (actual_time() - now);
		usleep(limit / 1000);
	}
}

long int	real_time_of_death(t_thread philo)
{
	long int	limit;

	limit = actual_time() - philo.new_start;
	limit = philo.t_die - limit;
	if (limit < 0)
		limit = 0;
	return (limit);
}
