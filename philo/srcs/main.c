/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:21:09 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/15 16:59:10 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	break_conditions(t_thread *philo)
{
	time_t		timer;
	long int	time_of_death;

	if (philo->info->died == 0)
	{
		timer = get_time();
		time_of_death = timer - philo->last_meal;
		if (time_of_death >= philo->info->time_to_die || \
			(philo->info->number_of_philosophers == 1))
		{
			if (philo->info->number_of_philosophers == 1)
				usleep((philo)->info->time_to_die * 1000);
			pthread_mutex_lock(&philo->info->print);
			philo->info->died = philo->thread_id;
			philo->info->time_of_death = time_of_death;
			pthread_mutex_unlock(&philo->info->print);
			return (1);
		}
		if (philo->info->nb_of_times_each_philosopher_must_eat == \
			philo->nb_meal)
		{
			pthread_mutex_lock(&philo->info->print);
			philo->info->died = philo->thread_id;
			philo->info->time_of_death = 0;
			pthread_mutex_unlock(&philo->info->print);
			return (1);
		}
		return (0);
	}
	return (1);
}

void	*start(void *arg)
{
	t_thread	philo;

	philo = *(t_thread *)arg;
	if (philo.thread_id % 2 == 0 && philo.thread_id + 1 != philo.info->number_of_philosophers) \
		time_to_eat(&philo);
	while (1)
	{
		if (time_to_eat(&philo) == 1)
			break ;
		if (time_to_sleep(&philo) == 1)
			break ;
		if (time_to_think(&philo) == 1)
			break ;
	}
	return (0);
}

void	death_checker(t_info *info)
{
	while (1)
	{

		if (info->died >= 1)
		{
			pthread_mutex_lock(&info->print);
			if (info->time_of_death != 0)
				printf("%ld\t%d\t%s\n", info->time_of_death, info->died, DIED);
			pthread_mutex_unlock(&info->print);
			break ;
		}
	}
}

int	main(int ac, char **av)
{
	t_info	info;
	int		t;

	t = 0;
	if (valid(ac, av) != 0 || init_info(&info, ac, av) != 0)
		clean_exit(1, NULL);
	init_mutexes(&info);
	init_threads(&info, t);
	death_checker(&info);
	monitor_threads(&info, t);
	kill_mutexes(&info);
	clean_exit(4, &info);
}
