#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>//
# include <pthread.h>

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
    pthread_mutex_t    *mutex;
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

/*init.c*/
int     valid(int ac, char **av);
void    init_data(/*t_data **data, int ac, char **av*/);
void    init_philo(/*t_philo **philo, t_data **data*/);
int     init(t_philo **philo, t_data **data, int ac, char **av);
/*lib.c*/
int     is_num(char *str);
short	ft_atos(char *str);
/*message.c*/
void    clean_exit(t_philo **philo, t_data **data, int code, char *error);

#endif