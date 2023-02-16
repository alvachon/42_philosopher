#include "../include/philo.h"

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
