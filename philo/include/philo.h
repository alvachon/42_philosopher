/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:32:47 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/15 16:49:32 by alvachon         ###   ########.fr       */
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

typedef struct s_info
{
	long int		start;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_times_each_philosopher_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	long int		time_of_death;
	int				died;
	int				lock_forks;
	void			*array_keeper;
	pthread_t		*thread_keeper;
}					t_info;
typedef struct s_thread
{
	int				thread_id;
	long int		last_meal;
	int				nb_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_info			*info;
}					t_thread;

/*main*/
int					break_conditions(t_thread *philo);
void				*start(void *arg);
void				monitor_threads(t_info *info, int t);
void				kill_mutexes(t_info *info);
/*init*/
int					valid(int ac, char **av);
void				init_philo(t_thread *philo_id, t_info *info, int t);
void				init_threads(t_info *info, int t);
void				init_mutexes(t_info *info);
int					init_info(t_info *info, int ac, char **av);
/*utils*/
long int			get_time(void);
int					is_num(char *str);
int					ft_atoi(char *str);
int					clean_exit(int code, t_info *info);
/*action.c*/
void				print(int id, char *str, t_thread *philo);
int					time_to_think(t_thread *philo);
int					time_to_sleep(t_thread *philo);
int					time_to_eat(t_thread *philo);
void				lock_forks(t_thread *philo);
void				unlock_forks(t_thread *philo);

#endif
