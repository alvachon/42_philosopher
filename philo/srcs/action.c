/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:21:48 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/16 15:34:42 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print(int id, char *str, t_thread *philo)
{
	long int	time;

	time = get_time() - philo->info->start;
	pthread_mutex_lock(&philo->info->print);
	printf("%ld\t%d\t%s\n", time, id, str);
	pthread_mutex_unlock(&philo->info->print);
}

int	time_to_eat(t_thread *philo)
{
	if (conditions(philo) == 0)
	{
		lock_forks(philo);
		print(philo->thread_id, EAT, philo);
		usleep(philo->info->time_to_eat * 1000);
		philo->last_meal = get_time();
		if (philo->nb_meal != -1)
			philo->nb_meal += 1;
		unlock_forks(philo);
		if (time_to_sleep(philo) == 1)
			return (1);
		return (0);
	}
	return (1);
}

int	time_to_sleep(t_thread *philo)
{
	if (conditions(philo) == 0)
	{
		print(philo->thread_id, SLEEP, philo);
		usleep((philo)->info->time_to_sleep * 1000);
		return (0);
	}
	return (1);
}

int	time_to_think(t_thread *philo)
{
	print(philo->thread_id, THINK, philo);
	return (0);
}

void	lock_forks(t_thread *philo)
{
		pthread_mutex_lock(philo->l_fork);
		print(philo->thread_id, FORK, philo);
		pthread_mutex_lock(philo->r_fork);
		print(philo->thread_id, FORK, philo);
}

void	unlock_forks(t_thread *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
