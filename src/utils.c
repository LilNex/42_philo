/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:16:32 by lilnex            #+#    #+#             */
/*   Updated: 2023/08/02 17:21:31 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void print_config(t_config *config)
{
    printf("------- CONFIG --------\n");
    printf("num philos :    %d\n", config->num_philos);
    printf("time eat :      %d\n", config->time_eat);
    printf("time sleep :    %d\n", config->time_sleep);
    printf("time think :    %d\n", config->time_think);
}

long long get_current_tick(t_config *config, struct timeval time)
{
    long long   result;

    result = time.tv_sec - config->start_date.tv_sec;

    return (result);    
        
}

void print_log(t_config *config, char *str)
{
    struct timeval date_now;
    long long time;

    gettimeofday(&date_now, NULL);
    time = get_current_tick(config, date_now);
    printf("res of tick : %lld\n", time);
    printf("%lld | %s", time, str);
}