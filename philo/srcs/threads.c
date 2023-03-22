/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:58:49 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/21 19:42:29 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philo(t_thread *philo_id, t_info *info, int t)
{
	pthread_mutex_lock(&info->sim_start);
	(philo_id)->thread_id = t + 1;
	(philo_id)->nb_meal = info->must_eat_nb;
	(philo_id)->l_fork = &info->forks[t];
	(philo_id)->r_fork = &info->forks[(t + 1) % info->nb_philo];
	(philo_id)->t_die = info->time_to_die;
	(philo_id)->t_eat = info->time_to_eat;
	(philo_id)->t_sleep = info->time_to_sleep;
	(philo_id)->t_think = info->time_to_sleep + info->time_to_eat;
	(philo_id)->new_start = info->start;
	(philo_id)->nb = info->nb_philo;
	(philo_id)->philo_status = E_ALIVE;
	(philo_id)->info = info;
}

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
			return (3);
		pthread_mutex_unlock(&info->sim_start);
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
