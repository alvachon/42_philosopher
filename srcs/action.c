/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:21:48 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/11 17:21:51 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    printeur(long time, int id, char *str, t_thread *philo)
{
    pthread_mutex_lock(&philo->info->print);
    printf("%ld\t%d\t%s\n", time, id, str);
    pthread_mutex_unlock(&philo->info->print);
}

void    time_to_think(t_thread *philo)
{
    printeur(get_time() - philo->info->start, philo->thread_id, "is thinking", philo);
}

void    time_to_sleep(t_thread *philo)
{
    printeur(get_time() - philo->info->start, philo->thread_id, "is sleeping", philo);
    waitsys(philo->info->time_to_sleep);
}

void    time_to_eat(t_thread *philo)
{
    pthread_mutex_lock(philo->l_fork);
    pthread_mutex_lock(philo->r_fork);
    printeur(get_time() - philo->info->start, philo->thread_id, "as taken a fork", philo);
    printeur(get_time() - philo->info->start, philo->thread_id, "as taken a fork", philo);
    printeur(get_time() - philo->info->start, philo->thread_id, "is eating", philo);
    waitsys(philo->info->time_to_eat);
    (philo)->last_meal = get_time();
    if (philo->nb_meal != -1)
        (philo)->nb_meal += 1;
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    printeur(get_time() - philo->info->start, philo->thread_id, "as left a fork", philo);
    printeur(get_time() - philo->info->start, philo->thread_id, "as left a fork", philo);
}
