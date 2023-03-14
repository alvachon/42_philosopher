/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:21:09 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/14 10:34:13 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	break_conditions(t_thread *philo)
{
	time_t	timer;

	timer = get_time();
	if (timer - philo->last_meal >= philo->info->time_to_die)
	{
		printeur(get_time() - philo->info->start, philo->thread_id, "died", \
				philo);
		return (1);
	}
	if (philo->info->nb_of_times_each_philosopher_must_eat == philo->nb_meal)
		return (1);
	if (philo->info->number_of_philosophers == 1)
	{
		waitsys(philo->info->time_to_die);
		printeur(get_time() - philo->info->start, philo->thread_id, "died", \
				philo);
		return (1);
	}
	return (0);
}

void	*start(void *arg)
{
	t_thread	philo;

	philo = *(t_thread *)arg;
	while (1)
	{
		if (break_conditions(&philo) != 0)
			break ;
		if (philo.thread_id % 2 == 0 && philo.thread_id
			+ 1 != philo.info->number_of_philosophers)
			time_to_eat(&philo);
		else
			time_to_eat(&philo);
		if (break_conditions(&philo) != 0)
			break ;
		time_to_sleep(&philo);
		if (break_conditions(&philo) != 0)
			break ;
		time_to_think(&philo);
	}
	return (0);
}

void	kill_threads(t_info *info)
{
	int	t;

	t = 0;
	while (t < info->number_of_philosophers)
	{
		if (pthread_join(info->thread_keeper[t], NULL) != 0)
			return ;
		t++;
	}
}

void	kill_mutexes(t_info *info)
{
	int	count;

	count = info->number_of_philosophers;
	while (count--)
		pthread_mutex_destroy(&info->forks[count]);
	pthread_mutex_destroy(&info->print);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (valid(ac, av) != 0 || init_info(&info, ac, av) != 0)
		return (1);
	init_mutexes(&info);
	init_threads(&info);
	kill_threads(&info);
	kill_mutexes(&info);
	free(info.array_keeper);
	free(info.thread_keeper);
	free(info.forks);
}
