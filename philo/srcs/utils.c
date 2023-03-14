/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:20:19 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/14 12:45:32 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	get_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		exit(1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (*str == '+')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (0);
	else if (!(str[i] >= '0' && str[i] <= '9'))
		return (1);
	return (1);
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

//ft_exit();
