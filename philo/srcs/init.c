/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:16:24 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/21 15:01:19 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_num(char *str)
{
	if (*str == '+')
		str++;
	while (*str)
	{
		if (*str <= 32)
			str++;
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	nb;

	while (*str <= 32)
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	nb = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

int	valid(int ac, char **av)
{
	while (ac-- > 1)
	{
		if (is_num(av[ac]) == 1)
			return (1);
		if (ft_atoi(av[ac]) > INT_MAX || ft_atoi(av[ac]) < 0)
			return (1);
	}
	return (0);
}

int	init_info(t_info *info, int ac, char **av)
{
	info->start = actual_time();
	info->nb_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		info->must_eat_nb = -1;
	if (ac == 6)
		info->must_eat_nb = ft_atoi(av[5]);
	info->status = E_ALIVE;
	return (0);
}
