#include "../include/philo.h"

pthread_mutex_t  mutex;

void  *routine(void *arg)
{
  t_info      reservation;
  t_viewpoint *philosopher_id;
 
  philosopher_id = NULL;
  reservation = *(t_info *)arg;
  philosopher_id = malloc(sizeof(t_viewpoint));
  if (!philosopher_id)
    clean_exit(NULL, 3, MEM_MALLOC);//a changer
  philosopher_id->fork = NULL;
  template_client(&philosopher_id, &reservation);
  printf("philosopher_id->id %d\n", philosopher_id->id);
  /*pthread_mutex_lock(&mutex);
  mails++;
  pthread_mutex_unlock(&mutex);*/
  //free(arg);
  //free(philosopher_id);
  return (0);
}

int start(t_info *reservation)
{
  pthread_t thread[reservation->number_of_philosophers];

  pthread_mutex_init(&mutex, NULL);
  while (reservation->i < reservation->number_of_philosophers)
  {
    if (pthread_create(thread + reservation->i, NULL, &routine, (void *)reservation) != 0)
      return (1);
    printf("Thread %d has started\n", reservation->i);
    reservation->i++;
  }
  reservation->i = 0;
  while (reservation->i < reservation->number_of_philosophers)
  {
    if (pthread_join(thread[reservation->i], NULL) != 0)
      return (1);
    printf("Thread %d has finished execution\n", reservation->i);
    reservation->i++;
  }
  pthread_mutex_destroy(&mutex);
  return (0);
}

int main(int ac, char **av)
{
  //Each philosopher is a fork process
  //They take place via the general information that is given.
    t_info      *reservation;

    reservation = NULL;
    if ((valid(ac, av) == 0) && (init(&reservation, ac, av) == 0))
    {
        if (start(reservation) != 0)
           clean_exit(&reservation, 4, ERROR_THREAD);
    }
    else
      printf("nope\n");
    return (0);
}
