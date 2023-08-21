/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:29:29 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/21 01:43:32 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	ft_usleep(philo->config->time_sleep);
	print_log(philo, "is thinking");
}

void	take_fork(t_philo *philo)
{
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
		print_log(philo, "has died");
		pthread_mutex_lock(&philo->config->dead);
		philo->config->exit = 1;
		pthread_mutex_unlock(&philo->config->dead);
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
