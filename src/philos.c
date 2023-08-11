/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:32:01 by lilnex            #+#    #+#             */
/*   Updated: 2023/08/11 02:36:03 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*init_philo(t_config *conf, int i)
{
	t_philo	*p;

	(void) conf;
	p = ft_calloc(1, sizeof(t_philo));
	if (!p)
		return (p);
	p->num = i;
	p->config = conf;
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
	pthread_mutex_unlock(&conf->dead);
	gettimeofday(&conf->start_date, NULL);
	thread_checker(conf);
}

void	create_philos(t_config *config)
{
	int	i;

	i = 0;
	config->philos = ft_calloc(config->num_philos + 1, sizeof(t_philo *));
	while (i < config->num_philos)
	{
		config->philos[i] = init_philo(config, i);
		i++;
	}
	join_philos(config);
	printf("end thread\n");
}
