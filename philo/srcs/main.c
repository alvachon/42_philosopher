/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:21:09 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/16 16:04:52 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	conditions(t_thread *philo)
{
	long int	timestamp;
	long int	time_eat;
	long int	time_sleep;
	long int	time_die;

	timestamp = philo->info->start - philo->last_meal;
	time_eat = philo->info->time_to_eat;
	time_sleep = philo->info->time_to_sleep;
	time_die = philo->info->time_to_die;
	pthread_mutex_lock(&philo->info->print);
	if ((timestamp + time_eat) >= time_die)
	{
		printf("food\n");
		philo->died = 1;
		return (1);
	}
	if ((timestamp + time_sleep) >= time_die)
	{
		printf("sleep\n");
		philo->died = 1;
		return (1);
	}
	if ((timestamp + time_sleep + time_eat) >= time_die)
	{
		printf("both\n");
		philo->died = 1;
		return (1);
	}
	if (philo->nb_meal == philo->info->nb_of_times_each_philosopher_must_eat)
	{
		printf("nomnom\n");
		philo->food = 1;
		return (1);
	}
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}


void	*start(void *arg)
{
	t_thread	philo;

	philo = *(t_thread *)arg;
	if (philo.info->butler == 0)
	{
		while (philo.died == 0 || philo.food == 0)
		{
			if (time_to_eat(&philo) == 1 || philo.info->butler == 0)
				break ;
			if (time_to_think(&philo) == 1 || philo.info->butler == 0)
				break ;
		}
	}
	philo.info->butler = 1;
	pthread_mutex_unlock(&philo.info->print);
	return (0);
}

void	death_checker(t_info *info)
{
	while (1)
	{
		pthread_mutex_lock(&info->print);
		if (info->butler == 1)
			break ;
		pthread_mutex_unlock(&info->print);
	}
}

int	main(int ac, char **av)
{
	t_info	info;
	int		t;

	t = 0;
	if (ac < 5 || ac > 6)
		return (1);
	if (valid(ac, av) == 0 && (init_info(&info, ac, av) == 0))
	{
		init_mutexes(&info);
		init_threads(&info, t);
		monitor_threads(&info, t);
		death_checker(&info);
		kill_mutexes(&info);
		clean_exit(4, &info);
	}
	return (1);
}
