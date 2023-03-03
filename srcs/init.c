

#include "../include/philo.h"

int valid(int ac, char **av)
{
  if (ac < 5 || ac > 6)
    exit(1);//to change
  while (ac-- > 1)
  {
    if (is_num(av[ac]) == 1)
      exit(1);//to change
    if (ft_atoi(av[ac]) > INT_MAX || ft_atoi(av[ac]) < 0)
      exit(1);//to change
  }
  return (0);
}
