#include "../include/philo.h"

void  waitsys(time_t timer)
{
  time_t delay;

  delay = get_time() + timer;
  while (get_time() < delay)
    usleep(50);
}

void  time_to_sleep(t_thread *thread_data, pthread_mutex_t  *mutex)
{
  long  timestamp_in_ms;
  pthread_mutex_lock(&*mutex);
  timestamp_in_ms = get_time() - thread_data->reservation->start;
  printf("%ld %d %s\n", timestamp_in_ms, thread_data->thread_id, "is sleeping");
  waitsys(thread_data->reservation->time_to_sleep);
  pthread_mutex_unlock(&*mutex);
  return ;
}

void  time_to_eat(t_thread  *thread_data, pthread_mutex_t  *mutex)
{
  long  timestamp_in_ms;
  pthread_mutex_lock(&*mutex);
  timestamp_in_ms = get_time() - thread_data->reservation->start;
  printf("%ld %d %s\n", timestamp_in_ms, thread_data->thread_id, "is eating");
  thread_data->eat = 1;
  waitsys(thread_data->reservation->time_to_eat);
  pthread_mutex_unlock(&*mutex);
  time_to_sleep(&*thread_data, &*mutex);
}

void  thinking(t_thread  *thread_data, pthread_mutex_t  *mutex)
{
  long  timestamp_in_ms;
  pthread_mutex_lock(&*mutex);
  timestamp_in_ms = get_time() - thread_data->reservation->start;
  printf("%ld %d %s\n", timestamp_in_ms, thread_data->thread_id, "is thinking");
  pthread_mutex_unlock(&*mutex);
  return ;
}

void  *routine(void *arg)
{
  pthread_mutex_t  mutex;
  t_thread         thread_data;
  int              loop;

  loop = 5;
  pthread_mutex_init(&mutex, NULL);
  thread_data = *(t_thread *)arg;
  if ((thread_data.team == 'R' && thread_data.eat == 0) \
    && (thread_data.team == 'B' && thread_data.eat == 0))
    {
      if (thread_data.team == 'R')
        time_to_eat(&thread_data, &mutex);
      else
        thinking(&thread_data, &mutex);
    }
  while (loop > 0)
  {
    time_to_eat(&thread_data, &mutex);
    thinking(&thread_data, &mutex);
    loop--;
  }
  pthread_mutex_destroy(&mutex);
  return (0);
}

void  set_team(int t, t_thread  *thread_data_array, t_info *reservation)
{
  thread_data_array->thread_id = t + 1;
  thread_data_array->reservation = reservation;
  if ((t + 1) == reservation->number_of_philosophers && reservation->number_of_philosophers % 2 != 0)
    thread_data_array->team = 'V';
  else if ((t + 1) % 2 == 0)
    thread_data_array->team = 'R';
  else
    thread_data_array->team = 'B';
}

int start(t_info *reservation)
{
  int        t;
  pthread_t  threads[reservation->number_of_philosophers];
  t_thread   thread_data_array[reservation->number_of_philosophers];

  t = 0;
  while (t < reservation->number_of_philosophers)
  {
    set_team(t, &thread_data_array[t], reservation);
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
