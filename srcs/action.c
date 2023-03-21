/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:21:48 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/20 20:00:47 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print(t_thread *philo, char *message)
{
	long int	time;

	pthread_mutex_lock(&philo->info->print);
	time = actual_time(philo->info) - philo->info->start;
	if (ft_strcmp(DIED, message) == 0 && philo->info->dead == 0)
	{
		printf("%ld\t%d\t%s\n", time, philo->thread_id, message);
		philo->info->dead = 1;
	}
	if (philo->info->dead != 1)
		printf("%ld\t%d\t%s\n", time, philo->thread_id, message);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}

int	time_to_eat(t_thread *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	print(philo, FORK);
	print(philo, FORK);
	ms_wait(*philo, philo->info->time_to_eat);
	print(philo, EAT);
	philo->last_meal = actual_time(philo->info);
	if (philo->nb_meal != -1 || philo->nb_meal == philo->info->nb_philo)
		philo->nb_meal += 1;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	ms_wait(*philo, philo->info->time_to_sleep);
	print(philo, SLEEP);
	return (0);
}
