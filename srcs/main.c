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

int main(int ac, char **av)
{
  t_info  info;

  if (valid(ac, av) != 0 || init_info(&info, ac, av) != 0)
    return (1);
  init_mutexes(&info);
  init_threads(&info);

  //clean (destroy action)
}

/*
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
}*/