#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>//
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

#define ERROR_ARG "Invalid argument quantity\n"
#define ERROR_INPUT "Invalid Input\n"
#define ERROR_RANGE "Invalid range\n"
#define MEM_MALLOC  "Not enough space to allocate\n"
#define ERROR_DATA "Invalid data\n"
#define ERROR_ID  "Invalid philo\n"
#define ERROR_THREAD "Failed to create thread\n"
typedef struct s_info
{
    long   start;
    int    number_of_philosophers;
    int    time_to_die;
    int    time_to_eat;
    int    time_to_sleep;
    int    number_of_times_each_philosopher_must_eat;
    int    a_thread_died;//
    int    eat_done;//
}   t_info
;

typedef struct s_thread
{
    int               thread_id;
    pthread_mutex_t   a_fork;
    long              last_meal;
    int               nb_meal;
    t_info            *reservation;
}   t_thread
;

/*
Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
*/

/*init.c*/
int             valid(int ac, char **av);
//void            info_reservation(t_info **reservation, int ac, char **av);
//int             init(t_info **reservation, int ac, char **av);
/*lib.c*/
int	            ft_strcmp(char *s1, char *s2);
long            get_time(void);
int             is_num(char *str);
int             ft_atoi(char *str);
/*message.c*/
//void            clean_exit(t_info **reservation, int code, char *error);

void            printer_info(t_info *info);

#endif