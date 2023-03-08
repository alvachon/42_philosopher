/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:16:24 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/07 15:16:26 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int valid(int ac, char **av)
{
  if (ac < 5 || ac > 6)
    exit(1);//to change
  while (ac-- > 1)
  {
    if (is_num(av[ac]) == 1)
      exit(1);//to change
    if (ft_atoi(av[ac]) > INT_MAX || ft_atoi(av[ac]) < 0)
      exit(1);//to change
  }
  return (0);
}

int   read_future(t_info *info)
{
  if (info->time_to_eat > info->time_to_die)
    return (1);
  if (info->time_to_sleep > info->time_to_die)
    return (1);
  if ((info->time_to_eat + info->time_to_sleep) > info->time_to_die)
    return (1);
  if (info->number_of_philosophers == 1)
    return (1);
  if (info->time_to_eat > info->time_to_sleep)
  {
    if (info->number_of_philosophers % 2 == 0)
    {
      if ((info->time_to_die * 2) < (info->time_to_eat + info->time_to_sleep))
        return (1);
    }
    else
    {
      if ((info->time_to_die * 3) < (info->time_to_eat + info->time_to_sleep))
        return (1);
    }
  }
  if (info->number_of_times_each_philosopher_must_eat != -1)
    return (0);//
  return (0);
}

long  set_time_of_death(t_info *info, int r)
{
  if (r == 1)
    return ((long)info->time_to_die);
  return (0);
}

void  set_info(t_info **info, int ac, char **av)
{
  int r;

  (*info)->start = get_time();
  (*info)->number_of_philosophers = ft_atoi(av[1]);
  (*info)->time_to_die = ft_atoi(av[2]);
  (*info)->time_to_eat = ft_atoi(av[3]);
  (*info)->time_to_sleep = ft_atoi(av[4]);
  if (ac == 5)
    (*info)->number_of_times_each_philosopher_must_eat = -1;
  if (ac == 6)
    (*info)->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
  r = read_future(*info);
  if (r >= 1)
  {
    (*info)->will_die = 1;
    (*info)->time_of_death = set_time_of_death(*info, r);
  }
  r = 0;
  (*info)->fork = malloc(sizeof (pthread_mutex_t) * (*info)->number_of_philosophers);
  if ((*info)->fork == NULL)
    exit(1);//
}

void  set_thread(t_thread *thread, t_info *info, int t)
{
  thread->thread_id = t;
  thread->reservation = info;
  thread->last_meal = get_time() - info->start;
  thread->nb_meal = 0;
  pthread_mutex_init(&thread->reservation->fork[t], NULL);
  thread->l_fork = t;
  if (info->number_of_philosophers % 2 != 0 && t == info->number_of_philosophers)
    thread->r_fork = 0;
  else
    thread->r_fork = t + 1;
}
