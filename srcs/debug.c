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
    printf("\ninfo->start : %ld\n", info->start);
    printf("info->number_of_philosophers : %d\n", info->number_of_philosophers);
    printf("info->time_to_die : %d\n", info->time_to_die);
    printf("info->time_to_eat : %d\n", info->time_to_eat);
    printf("info->time_to_sleep : %d\n", info->time_to_sleep);
    printf("info->will_die : %d\n", info->will_die);
    printf("info->time_of_death: %ld\n", info->time_of_death);
    printf("number_of_times_each_philosopher_must_eat : %d\n\n", info->number_of_times_each_philosopher_must_eat);
}

void    printer_thread(t_thread *thread)
{
    printf("\nthread->thread_id %d\n", thread->thread_id);
    printf("thread->last_meal %ld\n", thread->last_meal);
}