

#include "../include/philo.h"

int valid(int ac, char **av)
{
  if (ac < 5 || ac > 6)
    clean_exit(NULL, NULL, 2, ERROR_ARG);
  while (ac-- > 1)
  {
    if (is_num(av[ac]) == 1)
      clean_exit(NULL, NULL, 2, ERROR_INPUT);
    if (ft_atoi(av[ac]) > INT_MAX || ft_atoi(av[ac]) < 0)
      clean_exit(NULL, NULL, 2, ERROR_RANGE);
  }
  return (0);
}

void info_reservation(t_info **reservation, int ac, char **av)
{
  (*reservation)->start = get_time((*reservation)->start);
  (*reservation)->number_of_philosophers = ft_atoi(av[1]);
	(*reservation)->time_to_die = ft_atoi(av[2]);
	(*reservation)->time_to_eat = ft_atoi(av[3]);
	(*reservation)->time_to_sleep = ft_atoi(av[4]);
  //(*reservation)->time_thk = 0;
  //if with think ?
  (*reservation)->done = 0;
  (*reservation)->died = 0;
  if (ac == 5)
    (*reservation)->number_of_times_each_philosopher_must_eat = -1;
  if (ac == 6)
    (*reservation)->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
  printf("Information about the reservation has been taken, data must be provide one at a time\n");
  //clean_exit(NULL, data, 3, ERROR_DATA);
}

void template_client(t_viewpoint **philosopher_id, t_info **reservation)
{
  (*philosopher_id)->id = 0;
  (*philosopher_id)->last_meal = 0;
  (*philosopher_id)->have_finished = 0;
  (*philosopher_id)->about_to_die = 0;
  (*philosopher_id)->dead = 0;
  (*philosopher_id)->appetite = (*reservation)->number_of_times_each_philosopher_must_eat;
  (*philosopher_id)->lft_fork = (*philosopher_id)->id;
  (*philosopher_id)->rgt_fork = ((*philosopher_id)->id + 1) % (*reservation)->number_of_philosophers;
  printf("Template of client is done, each can ask one at a time the server about the reservation.\n");
  //clean_exit(philo, data, 4, ERROR_ID);
}

int init(t_info **reservation, t_viewpoint **philosopher_id, int ac, char **av)
{
  *reservation = malloc(sizeof(t_info));
  if (!(*reservation))
    clean_exit(NULL, NULL, 2, MEM_MALLOC);
  info_reservation(reservation, ac, av);
  *philosopher_id = malloc(sizeof(t_viewpoint));
  if (!(*philosopher_id))
    clean_exit(NULL, reservation, 3, MEM_MALLOC);
  (*philosopher_id)->fork = NULL;
  template_client(philosopher_id, reservation);
  return (0);
}