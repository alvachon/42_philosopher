#include "../include/philo.h"

//usleep 500
void  waitsys(int timer)
{
  long time;

  time = get_time();
  usleep(timer * 920);
  while (get_time() < time + timer)
    usleep(timer * 3);
}

void  *start(void *arg)
{
  int             i;
  t_thread        philo;
  pthread_mutex_t action;
  
  i = 0;
  philo = *(t_thread *)arg;
  pthread_mutex_init(&action, NULL);
  pthread_mutex_lock(&action);
  printf("philo.thread_id : %d,  last meal : %ld, time to die : %ld\n", philo.thread_id, philo.last_meal, philo.reservation->time_to_die);
  pthread_mutex_unlock(&action);
  while (1)
  {
    if (philo.last_meal != 0)
    {
        pthread_mutex_lock(&action);
        printf("philo.thread_id : %d,  last meal : %ld, time to die : %ld\n", philo.thread_id, philo.last_meal, philo.reservation->time_to_die);
        pthread_mutex_unlock(&action);
      /*
      i = check_time_to_die(philo, action);
      if (i == 1)
        break ;*/
    }
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
        exit(1);//
      set_info(&info, ac, av);
      array_thread = malloc(sizeof(t_thread) * info->number_of_philosophers);
      if (array_thread == NULL)
        exit(1);//
      while (t < info->number_of_philosophers)
      {
        set_thread(&array_thread[t], info, t);
        if (pthread_create(&threads[t], NULL, &start, &array_thread[t]) != 0)
          return (1);
        printf("Thread %d has started\n", t);
        t++;
      }
      t = 0;
      while (t < info->number_of_philosophers)
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