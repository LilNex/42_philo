/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:16:32 by lilnex            #+#    #+#             */
/*   Updated: 2023/08/21 01:54:30 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	to_ms(struct timeval datetime)
{
	return ((u_int64_t)datetime.tv_sec * 1000
		+ (u_int64_t)datetime.tv_usec / 1000);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(50);
	return (0);
}

void	print_log(t_philo *philo, char *str)
{
	struct timeval	date_now;
	long int		current_tick;

	if (is_exited(philo->config))
		return ;
	gettimeofday(&date_now, NULL);
	current_tick = to_ms(date_now) - to_ms(philo->config->start_date);
	pthread_mutex_lock(&philo->config->print);
	printf("%ld | philo %d %s\n",
		current_tick,
		philo->num, str);
	pthread_mutex_unlock(&philo->config->print);
}

int	is_exited(t_config *config)
{
	int val;

	val = 0;
	if (pthread_mutex_lock(&config->dead))
		return (1);
	val = config->exit;
	if (pthread_mutex_unlock(&config->dead))
		return (1);
	// printf("exit : %d\n", val);
	return (val);
}


/*
void	lock_all_mutexs(t_config *config)
{
	int	i;

	i = 0;
	while (config->philos[i])
	{
		pthread_mutex_unlock(&config->philos[i]->fork);
		pthread_mutex_unlock(&config->philos[i]->mut_last_eaten);
		i++;
	}
	i = 0;
	while (config->philos[i])
	{
		pthread_mutex_lock(&config->philos[i]->fork);
		pthread_mutex_lock(&config->philos[i]->mut_last_eaten);
		i++;
	}
}
*/
