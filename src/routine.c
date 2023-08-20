/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:29:29 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/20 17:51:09 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->dead);
	pthread_mutex_unlock(&philo->config->dead);
	print_log(philo, "is thinking");
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->config->philos[(philo->num + 1)
		% philo->config->num_philos]->fork);
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

int	routine_checker(t_philo *philo, struct timeval date_now)
{
	int	diff;

	pthread_mutex_lock(&philo->mut_last_eaten);
	diff = to_ms(date_now) - to_ms(philo->last_eaten);
	pthread_mutex_unlock(&philo->mut_last_eaten);
	if ((diff > 0) && diff > philo->config->time_die)
	{
		pthread_mutex_lock(&philo->config->dead);
		print_log(philo, "has died");
		pthread_mutex_lock(&philo->config->print);
		pthread_mutex_unlock(&philo->config->philos[(philo->num + 1)
			% philo->config->num_philos]->fork);
		pthread_mutex_unlock(&philo->fork);
		return (0);
	}
	return (1);
}

void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	ft_usleep(philo->config->time_sleep);
}

void	*philo_routine(void *conf)
{
	t_philo	*philo;

	philo = (t_philo *)conf;
	while (1)
	{
		pthread_mutex_lock(&philo->config->dead);
		pthread_mutex_unlock(&philo->config->dead);
		if (philo->num % 2 == 0)
			take_fork(philo);
		philo_sleep(philo);
		if (philo->num % 2)
			take_fork(philo);
	}
	return (NULL);
}
