#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>//
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info
{
    time_t            start;
    int               number_of_philosophers;
    time_t            time_to_die;
    int               time_to_eat;
    int               time_to_sleep;
    int               number_of_times_each_philosopher_must_eat;
    pthread_mutex_t   *forks;//
    pthread_mutex_t   print;//
    void              *array_keeper;//
    pthread_t         *thread_keeper;//
}   t_info
;
typedef struct s_thread
{
    int             thread_id;//
    time_t          last_meal;//
    int             nb_meal;//
    pthread_mutex_t *r_fork;//
    pthread_mutex_t *l_fork;//
    t_info          *info;//
}   t_thread
;

/*main*/
int             break_conditions(t_thread *philo);
void            *start(void *arg);
/*init*/
int             valid(int ac, char **av);
void            init_philo(t_thread *philo_id, t_info *info, int t);
void            init_threads(t_info *info);
void            init_mutexes(t_info *info);
int             init_info(t_info *info, int ac, char **av);
/*lib*/         //utils
long	        get_time(void);
void            waitsys(int micro_seconds);
int	            is_num(char *str);
int	            ft_atoi(char *str);
/*action.c*/
void            printeur(long time, int id, char *str, t_thread *philo);
void            time_to_think(t_thread *philo);
void            time_to_sleep(t_thread *philo);
void            time_to_eat(t_thread *philo);

#endif