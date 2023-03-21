/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:21:09 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/20 20:00:40 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
! Implement qt system
*/
int	break_conditions(t_thread *philo)
{
	long int	timer;
	long int	die;

	pthread_mutex_lock(&philo->info->lock_all);
	die = philo->info->time_to_die;
	if (!philo->last_meal)
		timer = actual_time(philo->info) - philo->info->start;
	else
		timer = actual_time(philo->info) - philo->last_meal;
	if (timer - die >= 0)
	{
		print(philo, DIED);
		pthread_mutex_unlock(&philo->info->lock_all);
		return (1);
	}
	if (philo->info->must_eat_nb == philo->nb_meal)
	{
		pthread_mutex_unlock(&philo->info->lock_all);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->lock_all);
	return (0);
}

void	*routine(void *arg)
{
	t_thread	philo;

	philo = *(t_thread *)arg;
	if (philo.thread_id % 2 != 0)
		usleep((philo.info->time_to_eat / 2) * 1000);
	while (philo.info->dead == 0)
	{
		if (break_conditions(&philo) != 0)
			break ;
		time_to_eat(&philo);
		if (break_conditions(&philo) != 0)
			break ;
		print(&philo, THINK);
		if (break_conditions(&philo) != 0)
			break ;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;
	int		t;
	int		r;

	if (ac < 5 || ac > 6)
		return (1);
	t = 0;
	if (valid(ac, av) == 0)
	{
		init_info(&info, ac, av);
		if (init_mutexes(&info) == 1)
			return (clean_exit(1, NULL, MALLOC));
		r = init_threads(&info, t);
		if (r == 1 || r == 2)
			return (clean_exit(r + 1, &info, MALLOC));
		else if (r == 3)
			return (clean_exit(r + 1, &info, PTHREAD_C));
		if (monitor_threads(&info, t) == 1)
			return (clean_exit(4, &info, PTHREAD_J));
		else
			clean_exit(4, &info, END);
	}
	return (1);
}
