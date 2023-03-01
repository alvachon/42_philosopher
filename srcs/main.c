#include "../include/philo.h"

void  *routine(void *arg)
{
  pthread_mutex_t  mutex;
  t_thread         thread_data;

  pthread_mutex_init(&mutex, NULL);
  thread_data = *(t_thread *)arg;
  pthread_mutex_lock(&mutex);
  printf("id : %d\n", thread_data.thread_id);
  pthread_mutex_unlock(&mutex);
  pthread_mutex_destroy(&mutex);
  return (0);
}

int start(t_info *reservation)
{
  int        t;
  pthread_t  threads[reservation->number_of_philosophers];
  t_thread   thread_data_array[reservation->number_of_philosophers];

  t = 0;
  while (t < reservation->number_of_philosophers)
  {
    thread_data_array[t].thread_id = t + 1;
    thread_data_array[t].appetite = reservation->number_of_times_each_philosopher_must_eat;
    thread_data_array[t].lft_fork = t + 1;
    thread_data_array[t].rgt_fork = (t + 1) % reservation->number_of_philosophers;
    thread_data_array[t].reservation = reservation;
    if (pthread_create(threads + t, NULL, &routine, (void *)&thread_data_array[t]) != 0)
      return (1);
    printf("Thread %d has started\n", t);
    t++;
  }
  t = 0;
  while (t < reservation->number_of_philosophers)
  {
    if (pthread_join(threads[t], NULL) != 0)
      return (1);
    printf("Thread %d has finished execution\n", t);
    t++;
  }
  return (0);
}

int main(int ac, char **av)
{
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
