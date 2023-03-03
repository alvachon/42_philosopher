/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:00:51 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/03 14:00:52 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    printer_info(t_info *info)
{
    printf("%ld\n", info->start);
    printf("%d\n", info->number_of_philosophers);
    printf("%d\n", info->time_to_die);
}