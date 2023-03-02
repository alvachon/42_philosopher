

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

void info_reservation(t_info **reservation, int ac, char **av)
{
  (*reservation)->start = get_time();
  (*reservation)->number_of_philosophers = ft_atoi(av[1]);
	(*reservation)->time_to_die = ft_atoi(av[2]);
	(*reservation)->time_to_eat = ft_atoi(av[3]);
	(*reservation)->time_to_sleep = ft_atoi(av[4]);
  if (ac == 5)
    (*reservation)->number_of_times_each_philosopher_must_eat = -1;
  if (ac == 6)
    (*reservation)->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
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