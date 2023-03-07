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

void    printeur(long time, int id, char *str, pthread_mutex_t print)
{
    pthread_mutex_lock(&print);
    printf("%ld\t%d\t%s\n", time, id, str);
    pthread_mutex_unlock(&print);
}

int  check_time_to_die(t_thread philo, pthread_mutex_t death)
{
  long            time;

  time = get_time() - philo.reservation->start;
  if (time == philo.reservation->time_of_death && philo.reservation->will_die >= 1)
  {
    printeur(get_time() - philo.reservation->start, philo.thread_id, "died", death);
    return (1);
  }
  return (0);
}

void    time_to_think(t_thread *philo, pthread_mutex_t think)
{
    long            time;

    time = get_time() - philo->reservation->start;
    printeur(get_time() - philo->reservation->start, philo->thread_id, "is thinking", think);
}

void    time_to_sleep(t_thread *philo, pthread_mutex_t sleep)
{
    long            time;
    
    time = get_time() - philo->reservation->start;
    printeur(get_time() - philo->reservation->start, philo->thread_id, "is sleeping", sleep);
    waitsys(philo->reservation->time_to_sleep);
    pthread_mutex_unlock(&sleep);
}

//faire un choix selon le numero d'ID
//unlock les fourchettes si meurt ?
//array de fournette struct avec un id de 1 ou de 0
void    time_to_eat(t_thread *philo, pthread_mutex_t eat)
{
    pthread_mutex_lock(&philo->a_fork);
    printeur(get_time() - philo->reservation->start, philo->thread_id, "as taken a fork", eat);
    pthread_mutex_lock(&philo->a_fork + 1);
    printeur(get_time() - philo->reservation->start, philo->thread_id, "as taken a fork", eat);
    printeur(get_time() - philo->reservation->start, philo->thread_id, "is eating", eat);
    waitsys(philo->reservation->time_to_eat);
    philo->last_meal = get_time() - philo->reservation->start;
    printeur(get_time() - philo->reservation->start, philo->thread_id, "as left a fork", eat);
    pthread_mutex_unlock(&philo->a_fork);
    printeur(get_time() - philo->reservation->start, philo->thread_id, "as left a fork", eat);
    pthread_mutex_unlock(&philo->a_fork + 1);
    time_to_sleep(philo, eat);
}
