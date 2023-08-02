/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:32:01 by lilnex            #+#    #+#             */
/*   Updated: 2023/08/02 17:34:15 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *philo_routine(void *conf)
{
    t_philo *config;

    config = (t_philo *)conf;
    while (1)
    {
        printf("philo %d is eatring\n", config->num);
        print_log(config->config, "philo eating\n");
        usleep(10000000);
    }
    
    return (NULL);
}

t_philo *init_philo(t_config *conf, int i)
{
    t_philo *p;

    (void) conf;
    p = ft_calloc(1, sizeof(t_philo));
    if (!p)
        return (p);
    p->num = i;
    p->config = conf;
    pthread_create(&p->thread, NULL, &philo_routine, p);
    gettimeofday(&p->start_date, NULL);
    printf("philo %d created \n", i);
    // conf->philos[i] = p;
        return p;
}

void join_philos(t_config *conf)
{
    int count;

    count = 0;
    while (count < conf->num_philos)
    {
        pthread_join(conf->philos[count]->thread, NULL);
        printf("thread %d joined \n", count);
        count++;
    }
    
    
}

void create_philos(t_config *config)
{
    int i;

    i = 0;
    config->philos = ft_calloc(config->num_philos + 1, sizeof(t_philo *));
    gettimeofday(&config->start_date, NULL);
    while (i < config->num_philos)
    {
        // puts("creating filos\n");
        print_log(config, "created filo");
        config->philos[i] = init_philo(config, i);
        // pthread_join(config->philos[i]->thread, NULL);
        // pthread_detach(config->philos[i]->thread);
        // pthread_join(config->philos[i]->thread, NULL);
        i++;
    }
    join_philos(config);
    printf("end thread\n");
}