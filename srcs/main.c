#include "../include/philo.h"

//usleep 500
void  waitsys(time_t timer)
{
  time_t delay;

  delay = get_time() + timer;
  while (get_time() <= delay)
  {
    if (get_time() == delay)
      return ;
  }
}

void  *start(void *arg)
{
  int             i;
  t_thread        philo;
  pthread_mutex_t action;
  
  i = 0;
  philo = *(t_thread *)arg;
  pthread_mutex_init(&action, NULL);
  while (1)
  {
    i = check_time_to_die(philo, action);
    if (i == 1)
      break ;
    time_to_eat(&philo, action);
    time_to_think(&philo, action);
  }
  pthread_mutex_destroy(&action);
  return (0);
}

int main(int ac, char **av)
{
    int             t;
    t_info          *info;
    t_thread        *array_thread;
    pthread_t       threads[ft_atoi(av[1])];

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
        printf("Thread %d has started\n", t);
        t++;
      }
      t = 0;
      while (t < ft_atoi(av[1]))
      {
        if (pthread_join(threads[t], NULL) != 0)
          return (1);
        printf("Thread %d has finished\n", t);
        t++;
      }
      free(array_thread);
      free(info);
    }
    return (0);
}
//desyncroniser 