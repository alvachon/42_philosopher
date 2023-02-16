

#include "../include/philo.h"

int valid(int ac, char **av)
{
  if (ac < 5 || ac > 6)
    clean_exit(NULL, NULL, 2, ERROR_ARG);
  while (ac-- > 1)
  {
    if (is_num(av[ac]) == 1)
      clean_exit(NULL, NULL, 2, ERROR_INPUT);
    if (ft_atos(av[ac]) > (short)INT_MAX || ft_atos(av[ac]) < 0)
      clean_exit(NULL, NULL, 2, ERROR_RANGE);
  }
  return (0);
}

void init_data(t_data **data, int ac, char **av)
{
  (*data)->philo_nb = ft_atos(av[1]);
	(*data)->time_die = ft_atos(av[2]);
	(*data)->time_eat = ft_atos(av[3]);
	(*data)->time_slp = ft_atos(av[4]);
  (*data)->time_thk = 0;
  //if with think ?
  (*data)->done = 0;
  (*data)->died = 0;
  if (ac == 5)
    (*data)->eat_trig = -1;
  if (ac == 6)
    (*data)->eat_trig = ft_atos(av[5]);
  
  printf("ok init data\n");
  //clean_exit(NULL, data, 3, ERROR_DATA);
}

void init_philo(/*t_philo **philo, t_data **data*/)
{
  printf("ok init philo\n");
  //clean_exit(philo, data, 4, ERROR_ID);
}

int init(t_philo **philo, t_data **data, int ac, char **av)
{
  *data = malloc(sizeof(t_data));
  if (!(*data))
    clean_exit(NULL, NULL, 2, MEM_MALLOC);
  (*data)->mutex = NULL;
  init_data(data, ac, av);
  *philo = malloc(sizeof(t_philo));
  if (!(*philo))
    clean_exit(NULL, data, 3, MEM_MALLOC);
  (*philo)->fork = NULL;
  init_philo(/*philo, data*/);
  return (0);
}