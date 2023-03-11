/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:15:37 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/07 15:15:39 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    printeur(long time, int id, char *str, t_thread *philo)
{
    pthread_mutex_lock(&philo->info->action);
    printf("%ld\t%d\t%s\n", time, id, str);
    pthread_mutex_unlock(&philo->info->action);
}

/*int  check_time_to_die(t_thread philo, pthread_mutex_t death)
{
  long   time;

    time = get_time() - philo.last_meal;
    if (time > philo.info->time_to_die && philo.info->will_die >= 1)
    {
      printeur(get_time() - philo.info->start, philo.thread_id, "died", death);
      return (1);
    }
    return (0);
}*/

void    time_to_think(t_thread *philo)
{
    long    time;

    time = get_time() - philo->info->start;
    printeur(get_time() - philo->info->start, philo->thread_id, "is thinking", philo);
}

void    time_to_sleep(t_thread *philo)
{
    long    time;
    
    time = get_time() - philo->info->start;
    printeur(get_time() - philo->info->start, philo->thread_id, "is sleeping", philo);
    pthread_mutex_lock(&philo->info->action);
    waitsys(philo->info->time_to_sleep);
    pthread_mutex_unlock(&philo->info->action);
}

void    time_to_eat(t_thread *philo)
{
    pthread_mutex_lock(&philo->l_fork);
    printeur(get_time() - philo->info->start, philo->thread_id, "as taken a fork", philo);
    pthread_mutex_lock(&philo->r_fork);
    printeur(get_time() - philo->info->start, philo->thread_id, "as taken a fork", philo);
    printeur(get_time() - philo->info->start, philo->thread_id, "is eating", philo);
    waitsys(philo->info->time_to_eat);
    philo->last_meal = get_time() - philo->info->start;
    printeur(get_time() - philo->info->start, philo->thread_id, "as left a fork", philo);
    pthread_mutex_unlock(&philo->l_fork);
    printeur(get_time() - philo->info->start, philo->thread_id, "as left a fork", philo);
    pthread_mutex_unlock(&philo->r_fork);
}
