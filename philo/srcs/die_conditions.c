/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:51:23 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/24 10:34:31 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	wait_lock_die(t_thread *philo)
{
	pthread_mutex_lock(&philo->info->sim_end);
	ms_wait(real_time_of_death(*philo));
	philo->philo_status = E_DEAD;
	pthread_mutex_unlock(&philo->info->sim_end);
	print(philo, DIED);
}

int	one_philo(t_thread *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print(philo, FORK);
	wait_lock_die(philo);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

int	do_last(t_thread *philo, t_status status)
{
	lock_print_forks(philo);
	print(philo, EAT);
	set_new_attributes(philo);
	if (status == E_EAT)
	{
		wait_lock_die(philo);
		unlock_forks(philo);
		return (1);
	}
	else
		ms_wait(philo->t_eat);
	unlock_forks(philo);
	print(philo, SLEEP);
	if (status == E_SLEEP)
	{
		wait_lock_die(philo);
		return (1);
	}
	else
		ms_wait(philo->t_sleep);
	print(philo, THINK);
	if (status == E_EVEN || status == E_ODD || status == E_THINK)
		wait_lock_die(philo);
	return (1);
}
