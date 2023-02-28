#include "../include/philo.h"

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