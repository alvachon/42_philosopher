/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:21:48 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/24 12:55:01 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_new_attributes(t_thread *philo)
{
	philo->new_start = actual_time();
	if (philo->nb_meal > 0)
		philo->nb_meal -= 1;
}

void	lock_print_forks(t_thread *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print(philo, FORK);
	pthread_mutex_lock(philo->l_fork);
	print(philo, FORK);
}

void	unlock_forks(t_thread *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	print(t_thread *philo, char *message)
{
	long int	time;

	pthread_mutex_lock(&philo->info->print);
	if (philo->info->status == E_DEAD)
	{
		pthread_mutex_unlock(&philo->info->print);
		return (0);
	}
	time = actual_time() - philo->info->start;
	if (philo->philo_status == E_DEAD)
	{
		pthread_mutex_lock(&philo->info->sim_end);
		printf("%ld\t%d\t%s\n", time, philo->thread_id, message);
		philo->info->status = E_DEAD;
		pthread_mutex_unlock(&philo->info->sim_end);
	}
	else
		printf("%ld\t%d\t%s\n", time, philo->thread_id, message);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}

void	*do_stuff(t_thread *philo)
{
	lock_print_forks(philo);
	print(philo, EAT);
	set_new_attributes(philo);
	ms_wait(philo->t_eat);
	unlock_forks(philo);
	if (philo->nb_meal == 0)
		return (0);
	print(philo, SLEEP);
	ms_wait(philo->t_sleep);
	print(philo, THINK);
	return (0);
}
