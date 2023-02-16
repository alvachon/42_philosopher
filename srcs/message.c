#include "../include/philo.h"

void  clean_exit(t_philo **philo, t_data **data, int code, char *error)
{
  if (code == 2)
  {
    perror(error);
    exit (EXIT_FAILURE);
  }
  if (code == 3)
  {
    free(*data);
    perror(error);
    exit (EXIT_FAILURE);
  }
  if (code == 4)
  {
    free(*data);
    free(*philo);
    perror(error);
    exit (EXIT_FAILURE);
  }
}