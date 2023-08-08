/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:16:32 by lilnex            #+#    #+#             */
/*   Updated: 2023/08/09 00:39:36 by ichaiq           ###   ########.fr       */
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

long long get_time_exec(t_config *config, struct timeval time)
{
    long long   result;

    // result = ((time.tv_sec - config->start_date.tv_sec) * 1000 )
                // + (time.tv_sec - config->start_date.tv_usec) / 1000;
    // result = (time.tv_sec * 1000 + config->start_date.tv_usec);
    result = to_ms(time) - to_ms(config->start_date);
    // printf("time : %lld\n",  to_ms(time));
    // printf("start date : %lld\n",  to_ms(config->start_date));

    return (result);    
        
}

long long to_ms(struct timeval datetime)
{
    return ((u_int64_t)datetime.tv_sec * 1000 + (u_int64_t)datetime.tv_usec / 1000);
}
// void	ft_usleep(long long time_in_ms)
// {
// 	struct timeval	current_time;
// 	struct timeval	start_time;
// 	long long		start_micros;
// 	long long		current_micros;

// 	time_in_ms = time_in_ms / 1000;
// 	gettimeofday(&start_time, NULL);
// 	start_micros = (start_time.tv_sec * (long long)1000000) + start_time.tv_usec;

// 	while (1)
// 	{
// 		gettimeofday(&current_time, NULL);
// 		current_micros = (current_time.tv_sec * (long long)1000000) + current_time.tv_usec;
// 		if ((current_micros - start_micros) >= time_in_ms * 1000)
// 			break;
// 		usleep(15);
// 	}
// }   


u_int64_t	get_time(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		return (perror("gettimeofday() FAILURE\n"), 0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;
    // time = time*1000*1000;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 100);
	return(0);
}

// void ft_usleep(long long usec)
// {
//     struct timeval now;

//     gettimeofday(&now, NULL);
//     usleep(usec);
// }


// void ft_usleep(long long time_in_ms)
// {
//     struct timespec start_time, current_time;
//     long long start_ns, current_ns;
//     time_in_ms = time_in_ms / 1000;

//     clock_gettime(CLOCK_MONOTONIC, &start_time);
//     start_ns = (start_time.tv_sec * 1000000000LL) + start_time.tv_nsec;

//     while (1)
//     {
//         clock_gettime(CLOCK_MONOTONIC, &current_time);
//         current_ns = (current_time.tv_sec * 1000000000LL) + current_time.tv_nsec;
//         if ((current_ns - start_ns) >= time_in_ms * 1000000LL)
//             break;
//         usleep(50);
//     }

// }
long int get_current_tick(struct timeval now, t_philo *philo)
{
    // printf("st diff : %lld\n",(to_ms(philo->start_date) - to_ms(philo->config->start_date)));
    // return ((to_ms(now) - to_ms(philo->config->start_date)
    //         )-(to_ms(philo->start_date) - to_ms(philo->config->start_date)));
    // printf("st diff : %lld\n",(to_ms(philo->start_date) - to_ms(philo->config->start_date)));
    return ((to_ms(now) - to_ms(philo->config->start_date)
            ));
}

void print_log(t_philo *philo, char *str)
{
    struct timeval date_now;
    // long long time;

    // time = get_time_exec(philo->config, date_now);
    // printf("res of tick : %lld\n", time);
    gettimeofday(&date_now, NULL);
    // pthread_mutex_lock(&philo->config->print);
    printf("%ld | philo %d %s\n",
            get_current_tick(date_now, philo),
            philo->num, str);
    // pthread_mutex_unlock(&philo->config->print);
}

void print_log_rev(t_philo *philo, char *str, struct timeval date_now)
{
    long long diff;

    diff = to_ms(date_now) - to_ms(philo->config->start_date);
    pthread_mutex_lock(&philo->config->print);
    printf("%lld | philo %d %s\n",
            diff,
            philo->num, str);
    pthread_mutex_unlock(&philo->config->print);
}