/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:55:10 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/20 14:16:14 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
* Actual time in MS (Miliseconds)
* Converting time in miliseconds:
* Seconds needs to be mutlplied by 1000;
* Microseconds need to be divided by 1000;*/
long int	actual_time(t_info *info)
{
	long int		time;
	long int		seconds;
	long int		microseconds;
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		clean_exit(4, info, TIME);
	seconds = (current_time.tv_sec * 1000);
	microseconds = (current_time.tv_usec / 1000);
	time = seconds + microseconds;
	return (time);
}

/*
* More precise usleep function that loop until reach limit.*/
void	ms_wait(t_thread philo, long int limit)
{
	long int	start;
	long int	timer;

	start = actual_time(philo.info);
	timer = (actual_time(philo.info) - start);
	while (timer < limit)
	{
		timer = (actual_time(philo.info) - start);
		usleep(limit / 1000);
	}
}
