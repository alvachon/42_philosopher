/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:16:24 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/16 15:50:12 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	valid(int ac, char **av)
{
	while (ac-- > 1)
	{
		if (is_num(av[ac]) == 1)
			return (1);
		if (ft_atoi(av[ac]) > INT_MAX || ft_atoi(av[ac]) < 0)
			return (1);
	}
	return (0);
}

void	init_philo(t_thread *philo_id, t_info *info, int t)
{
	(philo_id)->thread_id = t + 1;
	(philo_id)->nb_meal = 0;
	(philo_id)->last_meal = get_time();
	(philo_id)->l_fork = &info->forks[t];
	(philo_id)->r_fork = &info->forks[(t + 1) % info->number_of_philosophers];
	(philo_id)->info = info;
}

void	init_threads(t_info *info, int t)
{
	t_thread	*array_philo;
	pthread_t	*threads;

	array_philo = malloc(sizeof(t_thread) * info->number_of_philosophers);
	if (!array_philo)
		clean_exit(2, info);
	info->array_keeper = array_philo;
	threads = malloc(sizeof(pthread_t) * info->number_of_philosophers);
	if (!threads)
		clean_exit(3, info);
	info->thread_keeper = threads;
	while (t < info->number_of_philosophers)
	{
		init_philo(&array_philo[t], info, t);
		if (pthread_create(&threads[t], NULL, &start, \
				(void *)&array_philo[t]) != 0)
			return ;
		t++;
	}
	info->array_keeper = array_philo;
	info->thread_keeper = threads;
}

void	init_mutexes(t_info *info)
{
	int				count;
	pthread_mutex_t	*forks;

	count = info->number_of_philosophers;
	forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!forks)
		clean_exit(1, NULL);
	info->forks = forks;
	pthread_mutex_init(&info->print, NULL);
	while (count--)
		pthread_mutex_init(&forks[count], NULL);
	info->forks = forks;
}

int	init_info(t_info *info, int ac, char **av)
{
	info->start = get_time();
	info->number_of_philosophers = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		info->nb_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
		info->nb_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	info->lock_forks = 0;
	return (0);
}

void	kill_mutexes(t_info *info)
{
	int	count;

	count = info->number_of_philosophers;
	while (count--)
		pthread_mutex_destroy(&info->forks[count]);
	pthread_mutex_destroy(&info->print);
}

void	monitor_threads(t_info *info, int t)
{
	while (t < info->number_of_philosophers)
	{
		if (pthread_join(info->thread_keeper[t], NULL) != 0)
			return ;
		t++;
	}
}
