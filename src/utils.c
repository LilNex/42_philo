/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:16:32 by lilnex            #+#    #+#             */
/*   Updated: 2023/08/04 20:41:38 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void print_config(t_config *config)
{
    printf("------- CONFIG --------\n");
    printf("num philos :    %d\n", config->num_philos);
    printf("time eat :      %d\n", config->time_eat);
    printf("time sleep :    %d\n", config->time_sleep);
    printf("time die :    %d\n", config->time_die);
}

long long get_current_tick(t_config *config, struct timeval time)
{
    long long   result;

    // result = ((time.tv_sec - config->start_date.tv_sec) * 1000 )
                // + (time.tv_sec - config->start_date.tv_usec) / 1000;
    // result = (time.tv_sec * 1000 + config->start_date.tv_usec);
    result = to_ms(time) - to_ms(config->start_date);

    return (result);    
        
}

long long to_ms(struct timeval datetime)
{
    return (datetime.tv_sec * 1000 + datetime.tv_usec / 1000);
}

void ft_usleep(long long usec)
{
    struct timeval now;

    gettimeofday(&now, NULL);
    usleep(usec);
}

void print_log(t_philo *philo, char *str)
{
    struct timeval date_now;
    long long time;

    gettimeofday(&date_now, NULL);
    time = get_current_tick(philo->config, date_now);
    // printf("res of tick : %lld\n", time);
    printf("%lld | philo %d %s\n", time, philo->num, str);
}