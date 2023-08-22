/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:29:29 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/22 01:11:14 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	ft_usleep(philo->config->time_sleep);
	print_log(philo, "is thinking");
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (((philo->num + 1) % philo->config->num_philos) != philo->num)
		pthread_mutex_lock(&philo->config->philos[(philo->num + 1)
			% philo->config->num_philos]->fork);
	else
	{
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	print_log(philo, "has taken fork");
	print_log(philo, "is eating");
	pthread_mutex_lock(&philo->mut_last_eaten);
	gettimeofday(&philo->last_eaten, NULL);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mut_last_eaten);
	ft_usleep(philo->config->time_eat);
	pthread_mutex_unlock(&philo->config->philos[(philo->num + 1)
		% philo->config->num_philos]->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	*thread_checker(void *conf)
{
	int				i;
	struct timeval	date_now;
	t_config		*config;

	i = 0;
	config = (t_config *) conf;
	while (1 && !is_all_meals_eaten(config) && !is_exited(config))
	{
		gettimeofday(&date_now, NULL);
		while (i < config->num_philos)
			if (!routine_checker(config->philos[i++], date_now))
				return (set_exit(config, 1), destroy_config(config), NULL);
		if (i >= config->num_philos)
			i = 0;
	}
	destroy_config(config);
	return (NULL);
}

int	routine_checker(t_philo *philo, struct timeval date_now)
{
	int	diff;

	pthread_mutex_lock(&philo->mut_last_eaten);
	diff = to_ms(date_now) - to_ms(philo->last_eaten);
	pthread_mutex_unlock(&philo->mut_last_eaten);
	if ((diff > 0) && diff > philo->config->time_die)
	{
		print_log(philo, "has died");
		set_exit(philo->config, 1);
		return (0);
	}
	return (1);
}

void	*philo_routine(void *conf)
{
	t_philo	*philo;

	philo = (t_philo *)conf;
	if (!(philo->num % 2))
		ft_usleep(philo->config->time_eat);
	while (!is_exited(philo->config))
	{
		take_fork(philo);
		if (!is_exited(philo->config))
		{
			philo_sleep(philo);
		}
	}
	return (NULL);
}
