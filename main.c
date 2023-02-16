//#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>//
#include <pthread.h>

#define ERROR_ARG "Invalid argument quantity\n"
#define ERROR_INPUT "Invalid Input\n"
#define ERROR_RANGE "Invalid range\n"
#define MEM_MALLOC  "Not enough space to allocate\n"
#define ERROR_DATA "Invalid data\n"
#define ERROR_ID  "Invalid philo\n"

typedef struct s_data
{
    unsigned long      start;
    short              philo_nb;
    short              time_die;
    short              time_eat;
    short              time_slp;
    short              time_thk;
    short              eat_trig;
    int                done;
    int                died;
    pthread_mutex_t    mutex;
}   t_data
;

typedef struct s_philo
{
    unsigned long       last_meal;
    short               data_meal;
    short               lft_fork;
    short               rgt_fork;
    int                 id;
    pthread_mutex_t     *fork;
    t_data              *data;
}   t_philo
;

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (*str == '+')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
	  i++;
	if (str[i] == '\0')
	  return (0);
	if (!(str[i] >= '0' && str[i] <= '9'))
	  return (1);
}

long	ft_atol(char const *str)
{
	long	sign;
	long	nb;

	while (*str <= 32)
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	nb = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

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

int valid(int ac, char **av)
{
  if (ac < 5 || ac > 6)
    clean_exit(NULL, NULL, 2, ERROR_ARG);
  while (ac-- > 1)
  {
    if (is_num(av[ac]) == 1)
      clean_exit(NULL, NULL, 2, ERROR_INPUT);
    if (ft_atol(av[ac]) > INT_MAX || ft_atol(av[ac]) < 0)
      clean_exit(NULL, NULL, 2, ERROR_RANGE);
  }
  return (0);
}

void init_data(/*t_data **data, int ac, char **av*/)
{
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
  //(*data)->mutex = 0;
  init_data(/*data, ac, av*/);
  *philo = malloc(sizeof(t_philo));
  if (!(*philo))
    clean_exit(NULL, data, 3, MEM_MALLOC);
  //(*philo)->fork = NULL;
  init_philo(/*philo, data*/);
  return (0);
}

int main(int ac, char **av)
{
    t_data  *data;
    t_philo *philo;

    data = NULL;
    philo = NULL;
    if ((valid(ac, av) == 0) && (init(&philo, &data, ac, av) == 0))
    {
        printf("yey\n");
        /*if (start(philo, data))
            clean_exit(philo, data, EXIT_SUCCESS);*/
    }
    else
      printf("nope\n");
    return (0);
}
