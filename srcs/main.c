#include "../include/philo.h"

/*void  waitsys(time_t timer)
{
  time_t delay;

  delay = get_time() + timer;
  while (get_time() < delay)
    usleep(50);
}*/

void  *start(void *arg)
{
  t_thread        philo;
  pthread_mutex_t death;
  long            time;
  
  philo = *(t_thread *)arg;
  pthread_mutex_init(&death, NULL);
  if (philo.reservation->will_die >= 1)
  {
    pthread_mutex_lock(&death);
    time = get_time();
    printf("\nWhat time is it ? %ld\n\n", time);
    pthread_mutex_unlock(&death);
  }
  pthread_mutex_destroy(&death);
  return (0);
}

int main(int ac, char **av)
{
    int       t;
    t_info    *info;
    t_thread  *array_thread;
    pthread_t  threads[ft_atoi(av[1])];

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
        if (pthread_create(threads + t, NULL, &start, (void *)&array_thread[t]) != 0)
          return (1);
        printer_thread(&array_thread[t]);
        printf("\nThread %d has started\n", t);
        t++;
      }
      t = 0;
      while (t < ft_atoi(av[1]))
      {
        if (pthread_join(threads[t], NULL) != 0)
          return (1);
        printf("Thread %d has finished execution\n", t);
        t++;
      }
      printer_info(info);
      free(array_thread);
      free(info);
    }
    return (0);
}
