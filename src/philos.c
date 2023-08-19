/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilnex <lilnex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:32:01 by lilnex            #+#    #+#             */
/*   Updated: 2023/08/19 14:29:39 by lilnex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*init_philo(t_config *conf, int i)
{
	t_philo	*p;

	(void) conf;
	p = malloc(1 * sizeof(t_philo));
	if (!p)
		return (p);
	p->num = i;
	p->config = conf;
	p->meals_eaten = 0;
	pthread_mutex_init(&p->fork, NULL);
	pthread_mutex_init(&p->mut_last_eaten, NULL);
	return (p);
}

void	join_philos(t_config *conf)
{
	int		count;
	t_philo	*philo;

	count = 0;
	pthread_mutex_lock(&conf->dead);
	while (count < conf->num_philos)
	{
		philo = conf->philos[count++];
		gettimeofday(&philo->start_date, NULL);
		pthread_create(&philo->thread, NULL, &philo_routine, philo);
		gettimeofday(&philo->last_eaten, NULL);
	}
	gettimeofday(&conf->start_date, NULL);
	pthread_mutex_unlock(&conf->dead);
	thread_checker(conf);
	free(conf);
}

void	create_philos(t_config *config)
{
	int	i;

	i = 0;
	config->philos = malloc((config->num_philos + 1) * sizeof(t_philo *));
	if (!config->philos)
		return ;
	while (i < config->num_philos)
	{
		config->philos[i] = init_philo(config, i);
		i++;
	}
	config->philos[i] = NULL;
	join_philos(config);
}

void	destroy_thread(t_philo *philo)
{
	if (!philo)
		return ;

	pthread_detach(philo->thread);
	pthread_mutex_destroy(&philo->fork);
	pthread_mutex_destroy(&philo->mut_last_eaten);
}

void	destroy_config(t_config *config)
{
	int	i;

	i = 0;
	while (config->philos[i])
	{
		pthread_join(config->philos[i]->thread, NULL);
		pthread_mutex_destroy(&config->philos[i]->fork);
		pthread_mutex_destroy(&config->philos[i]->mut_last_eaten);
		free(config->philos[i++]);
	}
	free(config->philos);
	// pthread_mutex_unlock(&config->dead);
	pthread_mutex_destroy(&config->dead);
	pthread_mutex_destroy(&config->print);
}
