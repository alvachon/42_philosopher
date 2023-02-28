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
    unsigned long    start;
    int              number_of_philosophers;
    int              time_to_die;
    int              time_to_eat;
    int              time_to_sleep;
    //int            time_thk;
    int              number_of_times_each_philosopher_must_eat;// (stop simulation)
    int              done;
    int              died;
}   t_info
;

typedef struct s_viewpoint
{
    int               id;//as a number from 1 to number_of_philosophers
    unsigned long     last_meal;
    int               appetite;
    int               have_finished;
    int               about_to_die;
    int               dead;
    int               lft_fork;
    int               rgt_fork;
    pthread_mutex_t   *fork;
    t_info            *reservation;
}   t_viewpoint
;

/*
Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
*/

/*init.c*/
int             valid(int ac, char **av);
void            info_reservation(t_info **reservation, int ac, char **av);
void            template_client(t_viewpoint **philosopher_id, t_info **reservation);
int             init(t_info **reservation, t_viewpoint **philosopher_id, int ac, char **av);
/*lib.c*/
unsigned long	get_time(unsigned int start);
int             is_num(char *str);
int             ft_atoi(char *str);
/*message.c*/
void            clean_exit(t_viewpoint **philosopher_id, t_info **reservation, int code, char *error);

#endif