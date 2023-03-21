/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:03:07 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/21 15:16:58 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
Malloc for each fork serve to keep each adresses back to back
Trigger setted to kill mutexes in case of */
int	init_mutexes(t_info *info)
{
	int				count;
	pthread_mutex_t	*forks;

	count = info->nb_philo;
	forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!forks)
		return (1);
	info->forks = forks;
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->sim_start, NULL);
	pthread_mutex_init(&info->sim_end, NULL);
	while (count--)
		pthread_mutex_init(&forks[count], NULL);
	info->forks = forks;
	info->mutexes = 1;
	return (0);
}

void	kill_mutexes(t_info *info)
{
	int	count;

	count = info->nb_philo;
	while (count--)
		pthread_mutex_destroy(&info->forks[count]);
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->sim_start);
	pthread_mutex_destroy(&info->sim_end);
}

int	clean_exit(int code, t_info *info, char *message)
{
	if (code == 2 || code == 3)
	{
		if (info->forks)
			free(info->forks);
		if (info->mutexes == 1)
			kill_mutexes(info);
	}
	if (code == 3)
	{
		if (info->array)
			free(info->array);
		if (info->threads)
			free (info->threads);
	}
	printf("%s\n", message);
	return (1);
}
