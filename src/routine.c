/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:29:29 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/06 17:34:27 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void take_fork(t_philo *philo)
{
	// pthread_mutex_lock(&philo->config->print);
	print_log(philo, "is thinking");
	// pthread_mutex_unlock(&philo->config->print);
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->config->philos[(philo->num + 1) % philo->config->num_philos]->fork);
	pthread_mutex_lock(&philo->mut_last_eaten);
	// pthread_mutex_lock(&philo->config->print);
	print_log(philo, "has taken fork");
	gettimeofday(&philo->last_eaten, NULL);
	print_log(philo, "is eating");
	pthread_mutex_unlock(&philo->mut_last_eaten);
	// pthread_mutex_unlock(&philo->config->print);
	ft_usleep(philo->config->time_eat * 1000);
	pthread_mutex_unlock(&philo->config->philos[(philo->num + 1) % philo->config->num_philos]->fork);
	pthread_mutex_unlock(&philo->fork);
}

void philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	// printf("philo %d sleeping\n", philo->num);
	ft_usleep(philo->config->time_sleep * 1000);
}


void *philo_routine(void *conf)
{
	t_philo *philo;

	philo = (t_philo *)conf;
	while (1)
	{
		// pthread_mutex_lock(&philo->config->dead);
		// if (philo->config->died)
		// 	break;
		// pthread_mutex_unlock(&philo->config->dead);
		if (philo->num % 2 == 0)
			take_fork(philo);
		// else take_fork(philo);
		philo_sleep(philo);
		
		if (philo->num % 2)
			take_fork(philo);
		
		// printf("philo %d is eatring\n", philo->num);
		// print_log(philo->config, "philo eating\n");
		// usleep(10000000);
	}
	
	return (NULL);
}