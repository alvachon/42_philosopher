/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:58:49 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/20 20:02:59 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philo(t_thread *philo_id, t_info *info, int t)
{
	(philo_id)->thread_id = t + 1;
	(philo_id)->nb_meal = 0;
	(philo_id)->l_fork = &info->forks[t];
	(philo_id)->r_fork = &info->forks[(t + 1) % info->nb_philo];
	(philo_id)->info = info;
}

/*
* Each pthread_t have the data set of one item of array_philo*
* I keep all data for a better clean later */
int	init_threads(t_info *info, int t)
{
	t_thread	*array_philo;
	pthread_t	*threads;

	array_philo = malloc(sizeof(t_thread) * info->nb_philo);
	if (!array_philo)
		return (1);
	info->array = array_philo;
	threads = malloc(sizeof(pthread_t) * info->nb_philo);
	if (!threads)
		return (2);
	info->threads = threads;
	while (t < info->nb_philo)
	{
		init_philo(&array_philo[t], info, t);
		if (pthread_create(info->threads + t, NULL, &routine, \
			(void *)&array_philo[t]) != 0)
			return (2);
		t++;
	}
	info->array = array_philo;
	info->threads = threads;
	return (0);
}

int	monitor_threads(t_info *info, int t)
{
	while (t < info->nb_philo)
	{
		if (pthread_join(info->threads[t], NULL) != 0)
			return (1);
		t++;
	}
	return (0);
}
