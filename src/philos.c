/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:32:01 by lilnex            #+#    #+#             */
/*   Updated: 2023/08/06 19:25:58 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"



t_philo *init_philo(t_config *conf, int i)
{
	t_philo *p;

	(void) conf;
	p = ft_calloc(1, sizeof(t_philo));
	if (!p)
		return (p);
	p->num = i;
	p->config = conf;
	pthread_mutex_init(&p->fork, NULL);
	pthread_mutex_init(&p->mut_eaten, NULL);
	// gettimeofday(&p->start_date, NULL);
	// printf("philo %d created \n", i);
	// conf->philos[i] = p;
		return p;
}


void join_philos(t_config *conf)
{
	int count;
	t_philo *philo;

	count = 0;
	gettimeofday(&conf->start_date, NULL);
	while (count < conf->num_philos)
	{
		philo = conf->philos[count++];
		gettimeofday(&philo->start_date, NULL);
		pthread_mutex_lock(&philo->mut_eaten);
		pthread_create(&philo->thread, NULL, &philo_routine, philo);
		gettimeofday(&philo->last_eaten, NULL);
		philo->last_eaten.tv_usec += conf->time_die * 1000;
		pthread_mutex_unlock(&philo->mut_eaten);
		// usleep(1);
		// printf("thread %d joined \n", count);
	}
	// gettimeofday(&conf->start_date, NULL);
	thread_checker(conf);
	
	// pthread_join(conf->philos[0]->thread, NULL);
	
	
}

void create_philos(t_config *config)
{
	int i;

	i = 0;
	config->philos = ft_calloc(config->num_philos + 1, sizeof(t_philo *));
	while (i < config->num_philos)
	{
		// puts("creating filos\n");
		// print_log(config, "created filo");
		config->philos[i] = init_philo(config, i);
		// pthread_join(config->philos[i]->thread, NULL);
		// pthread_detach(config->philos[i]->thread);
		// pthread_join(config->philos[i]->thread, NULL);
		i++;
	}
	join_philos(config);
	printf("end thread\n");
}
