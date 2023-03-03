#include "../include/philo.h"

/*void  waitsys(time_t timer)
{
  time_t delay;

  delay = get_time() + timer;
  while (get_time() < delay)
    usleep(50);
}*/

void  set_info(t_info **info, int ac, char **av)
{
  (void)av;
  (*info)->start = get_time();
  (*info)->number_of_philosophers = ft_atoi(av[1]);
  (*info)->time_to_die = ft_atoi(av[2]);
  (*info)->time_to_eat = ft_atoi(av[3]);
  (*info)->time_to_sleep = ft_atoi(av[4]);
  if (ac == 5)
    (*info)->number_of_times_each_philosopher_must_eat = 0;//-1;
  if (ac == 6)
    (*info)->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
  (*info)->a_thread_died = 0;
  (*info)->eat_done = 0;
}

void  set_thread(t_thread *thread, t_info *info, int t)
{
  (void)*info;
  thread->thread_id = t;
  pthread_mutex_init(&thread->a_fork, NULL);
  thread->last_meal = get_time() - info->start;
  thread->nb_meal = 0;
  thread->reservation = info;
}

int main(int ac, char **av)
{
    int       t;
    t_info    *info;
    t_thread  *array_thread;

    t = 0;
    if ((valid(ac, av) == 0))
    {
      info = malloc(sizeof(t_info));
      if (info == NULL)
        exit(1);
      array_thread = malloc(sizeof(t_thread) * ft_atoi(av[1]));
      set_info(&info, ac, av);
      while (t < ft_atoi(av[1]))
      {
        set_thread(&array_thread[t], info, t + 1);
        printf(" id = %d\n", array_thread[t].thread_id);
        t++;
      }
      t = 0;
      printer_info(info);
      free(array_thread);
      free(info);
    }
    return (0);
}
