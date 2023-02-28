#include "../include/philo.h"

void  clean_exit(t_viewpoint **philosopher_id, t_info **reservation, int code, char *error)
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
  if (code == 4)
  {
    free(*reservation);
    free(*philosopher_id);//
    perror(error);
    exit (EXIT_FAILURE);
  }
}