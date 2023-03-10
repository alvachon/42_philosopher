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
    time_t            start;
    int               number_of_philosophers;
    time_t            time_to_die;
    time_t            time_to_eat;
    time_t            time_to_sleep;
    int               number_of_times_each_philosopher_must_eat;
    int               will_die;
    time_t            time_of_death;
    pthread_mutex_t   *fork;
}   t_info
;

typedef struct s_thread
{
    int             thread_id;
    time_t          last_meal;
    int             nb_meal;
    int             r_fork;//
    int             l_fork;//
    t_info          *reservation;
}   t_thread
;

/*
Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
*/

void            waitsys(int timer);
void            printeur(long time, int id, char *str, pthread_mutex_t print);
/*action.c*/
int             check_time_to_die(t_thread philo, pthread_mutex_t death);
void            time_to_eat(t_thread *philo, pthread_mutex_t eat);
void            time_to_sleep(t_thread *philo, pthread_mutex_t sleep);
void            time_to_think(t_thread *philo, pthread_mutex_t think);
/*init.c*/
int             valid(int ac, char **av);
int             read_future(t_info *info);
void            set_info(t_info **info, int ac, char **av);
void            set_thread(t_thread *thread, t_info *info, int t);
//int             init(t_info **reservation, int ac, char **av);
/*lib.c*/
int	            ft_strcmp(char *s1, char *s2);
long            get_time(void);
int             is_num(char *str);
int             ft_atoi(char *str);
/*message.c*/
//void            clean_exit(t_info **reservation, int code, char *error);

void            printer_info(t_info *info);
void            printer_thread(t_thread *thread);

#endif