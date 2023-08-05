/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:32:01 by lilnex            #+#    #+#             */
/*   Updated: 2023/08/05 00:41:49 by ichaiq           ###   ########.fr       */
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
	gettimeofday(&p->start_date, NULL);
	// printf("philo %d created \n", i);
	// conf->philos[i] = p;
		return p;
}

void thread_checker(t_config *conf)
{
	int	i;
	t_philo *philo;
	struct timeval date_now;

	i = 0;
	while (1)
	{
		while (i < conf->num_philos)
		{
			gettimeofday(&date_now, NULL);
			philo = conf->philos[i];
			// printf("diff : %lld\n",(to_ms(date_now) - to_ms(philo->last_eaten)));
			if ((to_ms(date_now) - to_ms(philo->last_eaten)) > conf->time_die){
				
				printf("PHILO %d HAS DIED !!!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", philo->num);
				print_log(philo, "has died");
				printf("diff : %lld\n",(to_ms(date_now) - to_ms(philo->last_eaten)));
				// printf("last eaten : %lld\n",to_ms(philo->last_eaten));
				// printf("now : %lld\n",to_ms(date_now));
				ft_usleep(200000);
			}
			i++;
		}
		if(i >= conf->num_philos)
			i = 0;
		
	}
	
}

void join_philos(t_config *conf)
{
	int count;
	t_philo *philo;

	count = 0;
	gettimeofday(&conf->start_date, NULL);
	while (count < conf->num_philos)
	{
		philo = conf->philos[count];
		pthread_create(&philo->thread, NULL, &philo_routine, philo);
		usleep(1);
		gettimeofday(&philo->start_date, NULL);
		gettimeofday(&philo->last_eaten, NULL);
		// printf("thread %d joined \n", count);
		count++;
	}
	gettimeofday(&conf->start_date, NULL);
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
