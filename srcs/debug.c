/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:00:51 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/03 14:00:52 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int break_conditions(t_thread *philo)
{
  pthread_mutex_lock(&philo->info->action);
  printf("time since start : %ld\n", get_time() - philo->info->start);
  pthread_mutex_unlock(&philo->info->action);
    return (0);
}

void  *start(void *arg)
{
  t_thread        philo;//
  
  philo = *(t_thread *)arg;
  while (1)
  {
    if (break_conditions(&philo) != 0)
        break ;
    time_to_eat(&philo);
    /*if (break_conditions(&philo) != 0)
        break ;*/
    time_to_sleep(&philo);
   /* if (break_conditions(&philo) != 0)
        break ;*/
    time_to_think(&philo);
  }
  return (0);
}