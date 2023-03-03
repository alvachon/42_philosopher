

#include "../include/philo.h"

int valid(int ac, char **av)
{
  if (ac < 5 || ac > 6)
    clean_exit(NULL, 2, ERROR_ARG);
  while (ac-- > 1)
  {
    if (is_num(av[ac]) == 1)
      clean_exit(NULL, 2, ERROR_INPUT);
    if (ft_atoi(av[ac]) > INT_MAX || ft_atoi(av[ac]) < 0)
      clean_exit(NULL, 2, ERROR_RANGE);
  }
  return (0);
}

t_forks *init_forks(int nb_philo)
{
  t_forks *forks;
  int     split;

  forks = malloc(sizeof(t_forks));
  if (nb_philo % 2 != 0)
    pthread_mutex_init(&forks->one, NULL);
  nb_philo--;
  split = nb_philo / 2;
  while (split > -1)
  {
    pthread_mutex_init(&forks->left_forks[split], NULL);
    pthread_mutex_init(&forks->right_forks[split], NULL);
    split--;
  }
}

void info_reservation(t_info **reservation, int ac, char **av)
{
  (*reservation)->start = get_time();
  (*reservation)->number_of_philosophers = ft_atoi(av[1]);
	(*reservation)->time_to_die = ft_atoi(av[2]);// * 1000;
	(*reservation)->time_to_eat = ft_atoi(av[3]);// * 1000;
	(*reservation)->time_to_sleep = ft_atoi(av[4]);// * 1000;
  if (ac == 5)
    (*reservation)->number_of_times_each_philosopher_must_eat = -1;
  if (ac == 6)
    (*reservation)->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
  (*reservation)->a_thread_died = 0;
  (*reservation)->eat_done = 0;
  (*reservation)->number_of_forks = init_forks(((*reservation)->number_of_philosophers));
  printf("Information about the reservation has been taken.\n");
  //clean_exit(NULL, data, 3, ERROR_DATA);
}

int init(t_info **reservation, int ac, char **av)
{
  *reservation = malloc(sizeof(t_info));
  if (!(*reservation))
    clean_exit(NULL, 2, MEM_MALLOC);
  info_reservation(reservation, ac, av);
  return (0);
}