/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:21:09 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/27 13:04:58 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_die_conditions(t_thread *philo)
{
	if (philo->nb == 1)
		return (one_philo(philo));
	else if (philo->t_die <= philo->t_eat)
		return (do_last(philo, E_EAT));
	else if (philo->t_die <= philo->t_sleep)
		return (do_last(philo, E_SLEEP));
	else if (philo->t_die <= (philo->t_eat + philo->t_sleep))
		return (do_last(philo, E_THINK));
	else if ((philo->nb % 2 == 0) && (philo->t_die < (philo->t_eat * 2)))
		return (do_last(philo, E_EVEN));
	else if ((philo->nb % 2 != 0) && (philo->t_die < (philo->t_eat * 3)))
		return (do_last(philo, E_ODD));
	return (0);
}

void	*routine(void *arg)
{
	t_thread	philo;

	philo = *(t_thread *)arg;
	if (philo.thread_id % 2 == 0)
		usleep((philo.t_die / 10) * 1500);
	if (check_die_conditions(&philo) == 1)
		return (0);
	else
	{
		while (philo.nb_meal)
			do_stuff(&philo);
		while (philo.nb_meal == -1)
			do_stuff(&philo);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;
	int		t;
	int		r;

	if (ac < 5 || ac > 6)
		return (1);
	t = 0;
	if (valid(ac, av) == 0)
	{
		init_info(&info, ac, av);
		if (init_mutexes(&info) == 1)
			return (clean_exit(1, NULL, MALLOC));
		r = init_threads(&info, t);
		if (r == 1 || r == 2)
			return (clean_exit(r + 1, &info, MALLOC));
		else if (r == 3)
			return (clean_exit(r + 1, &info, PTHREAD_C));
		if (monitor_threads(&info, t) == 1)
			return (clean_exit(3, &info, PTHREAD_J));
		else
			clean_exit(3, &info, END);
	}
	return (1);
}
