#include "../include/philo.h"

pthread_mutex_t  mutex;

int identification[5] = {1, 2, 3, 4, 5};

void  *routine(void *arg)
{
  int i;

  i = *(int *)arg;
  printf("%d\n", identification[i]);
  /*pthread_mutex_lock(&mutex);
  mails++;
  pthread_mutex_unlock(&mutex);*/
  free(arg);
  return (0);
}

int start(t_info *reservation, t_viewpoint *philosopher_id)
{
  pthread_t thread[reservation->number_of_philosophers];
  int       i;
  int       *a;

  i = 0;
  (void)philosopher_id;
  pthread_mutex_init(&mutex, NULL);
  while (i < reservation->number_of_philosophers)
  {
    a = malloc(sizeof(int));
    *a = i;
    if (pthread_create(thread + i, NULL, &routine, a) != 0)
      return (1);
    printf("Thread %d has started\n", i);
    i++;
  }
  i = 0;
  while (i < reservation->number_of_philosophers)
  {
    if (pthread_join(thread[i], NULL) != 0)
      return (1);
    printf("Thread %d has finished execution\n", i);
    i++;
  }
  pthread_mutex_destroy(&mutex);
  return (0);
}

int main(int ac, char **av)
{
  //Each philosopher is a fork process
  //They take place via the general information that is given.
    t_info      *reservation;
    t_viewpoint *philosopher_id;

    reservation = NULL;
    philosopher_id = NULL;
    if ((valid(ac, av) == 0) && (init(&reservation, &philosopher_id, ac, av) == 0))
    {
        if (start(reservation, philosopher_id) != 0)
           clean_exit(&philosopher_id, &reservation, 4, ERROR_THREAD);
    }
    else
      printf("nope\n");
    return (0);
}
