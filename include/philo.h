/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:39 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/21 15:24:02 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DIED "died"
# define FORK "as taken a fork"
# define TIME "error:\n gettimeofday"
# define MALLOC "error:\n memory"
# define PTHREAD_C "error:\n pthread_create"
# define PTHREAD_J "error:\n pthread_join"
# define END "exit:\n end of the program"

typedef enum e_status
{
	E_DEAD,
	E_ALIVE,
	E_EVEN,
	E_ODD,
	E_EAT,
	E_SLEEP,
	E_THINK,
}	t_status;

typedef struct s_info
{
	int long		start;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_nb;
	int				status;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	sim_start;
	pthread_mutex_t	sim_end;
	int				mutexes;
	void			*array;
	pthread_t		*threads;
}	t_info;

typedef struct s_thread
{
	int				thread_id;
	int long		new_start;
	int				nb_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				nb;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_think;
	int				must_eat_nb;
	int				philo_status;
	t_info			*info;
}	t_thread;

/* main */
int					check_die_conditions(t_thread *philo);
void				*routine(void *arg);

/*action.c*/
void				set_new_attributes(t_thread *philo);
void				lock_print_forks(t_thread *philo);
void				unlock_forks(t_thread *philo);
int					print(t_thread *philo, char *message);
void				*do_stuff(t_thread *philo);

/* die_conditions.c*/
void				wait_lock_die(t_thread *philo);
int					one_philo(t_thread *philo);
int					do_last(t_thread *philo, t_status status);

/*init.c*/
int					valid(int ac, char **av);
int					init_info(t_info *info, int ac, char **av);
int					is_num(char *str);
int					ft_atoi(char *str);

/* mutexes_exit.c*/
int					init_mutexes(t_info *info);
void				kill_mutexes(t_info *info);
int					clean_exit(int code, t_info *info, char *message);

/*threads.c*/
void				init_philo(t_thread *philo_id, t_info *info, int t);
int					init_threads(t_info *info, int t);
int					monitor_threads(t_info *info, int t);

/* time.c*/
long int			actual_time(void);
void				ms_wait(long int limit);
long int			real_time_of_death(t_thread philo);

#endif
