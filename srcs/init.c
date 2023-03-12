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
    return (1);
  while (ac-- > 1)
  {
    if (is_num(av[ac]) == 1)
      return (1);
    if (ft_atoi(av[ac]) > INT_MAX || ft_atoi(av[ac]) < 0)
      return (1);
  }
  return (0);
}

void init_philo(t_thread *philo_id, t_info *info, int t)
{
  (philo_id)->thread_id = t + 1;
  (philo_id)->nb_meal = 0;
  (philo_id)->last_meal = get_time();
  (philo_id)->l_fork = &info->forks[t];
  (philo_id)->r_fork = &info->forks[(t + 1) % info->number_of_philosophers];
  (philo_id)->info = info;
}

void init_threads(t_info *info)
{
  int       t;
  t_thread  *array_philo;
  pthread_t *threads;

  array_philo = malloc(sizeof(t_thread) * info->number_of_philosophers);
  if (!array_philo)
    return ;
  threads = malloc(sizeof(pthread_t) * info->number_of_philosophers);
  if (!threads)
    return ;
  t = 0;
  while (t < info->number_of_philosophers)
  {
    init_philo(&array_philo[t], info, t);
    if (pthread_create(&threads[t], NULL, &start, (void *)&array_philo[t]) != 0)
      return ;
    printf("Thread %d has started\n", t);
    t++;
  }
  info->array_keeper = array_philo;
  info->thread_keeper = threads;
}

void  init_mutexes(t_info *info)
{
  int count;
  pthread_mutex_t *forks;

  count = info->number_of_philosophers;
  forks = malloc(sizeof(pthread_mutex_t) * count);
  if (!forks)
    return ;
  pthread_mutex_init(&info->print, NULL);
  while (count--)
    pthread_mutex_init(&forks[count], NULL);
  info->forks = forks;
}

int  init_info(t_info *info, int ac, char **av)
{
  info->start = get_time();
  info->number_of_philosophers = ft_atoi(av[1]);
  info->time_to_die = ft_atoi(av[2]);
  info->time_to_eat = ft_atoi(av[3]);
  info->time_to_sleep = ft_atoi(av[4]);
  if (ac == 5)
    info->number_of_times_each_philosopher_must_eat = -1;
  if (ac == 6)
    info->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
  return (0);
}
