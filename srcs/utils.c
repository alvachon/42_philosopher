/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:20:19 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/11 17:20:20 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(void)
{
    struct timeval time; 
    gettimeofday(&time, NULL); // get current time
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void  waitsys(int micro_seconds)
{
  long time;

  time = get_time();
  usleep(micro_seconds * 920);
  while (get_time() < time + micro_seconds)
    usleep(micro_seconds * 3);
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
