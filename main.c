#include "philo.h"

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

int simple(int ac, char **av)
{
    return (1);
}

int valid(int ac, char **av)
{
    if (simple(ac, av))
        clean_exit(NULL, NULL, EXIT_SUCCESS);
    return (0);
}

int init();

int main(int ac, char **av)
{
    t_data  *data;
    t_philo *philo;

    data = NULL;
    philo = NULL;
    if (valid(ac, av) && init(&philo, &data, ac, av))
    {
        if (start(philo, data))
            clean_exit(data, philo, EXIT_SUCCESS;
    }
    clean_exit(data, philo, EXIT_FAILURE);
}
