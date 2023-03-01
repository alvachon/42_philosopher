#include "../include/philo.h"

void  clean_exit(t_info **reservation, int code, char *error)
{
  if (code == 2)
  {
    perror(error);
    exit (EXIT_FAILURE);
  }
  if (code == 3)
  {
    free(*reservation);
    perror(error);
    exit (EXIT_FAILURE);
  }
  if (code == 4)//
  {
    free(*reservation);
    perror(error);
    exit (EXIT_FAILURE);
  }
}