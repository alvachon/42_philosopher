/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:39 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/20 15:01:40 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h> //
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


typedef struct s_info
{
	time_t			start;
	int				nb_philo;
	time_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_nb;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	lock_all;
	int				mutexes;
	void			*array;
	pthread_t		*threads;
}	t_info;

typedef struct s_thread
{
	int				thread_id;
	time_t			last_meal;
	int				nb_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_info			*info;
}	t_thread;

/*
* main*/
int					break_conditions(t_thread *philo);
void				*routine(void *arg);

/*
*init.c*/ // et utils
int					valid(int ac, char **av);
int					init_info(t_info *info, int ac, char **av);
int					is_num(char *str);
int					ft_atoi(char *str);
int					ft_strcmp(char *s1, char *s2);

/*
* time.c*/
long int			actual_time(t_info *info);
void				ms_wait(t_thread philo, long int limit);

/*
* threads.c*/
void				init_philo(t_thread *philo_id, t_info *info, int t);
int					init_threads(t_info *info, int t);
int					monitor_threads(t_info *info, int t);

/*
*	mutexes_exit.c*/
int					init_mutexes(t_info *info);
void				kill_mutexes(t_info *info);
int					clean_exit(int code, t_info *info, char *message);

/*action.c*/
int					print(t_thread *philo, char *message);
int					time_to_eat(t_thread *philo);

#endif
