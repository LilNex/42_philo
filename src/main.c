/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:52:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/09 00:32:12 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


t_config *init_config()
{
	t_config	*config;
	
	config = ft_calloc(1, sizeof(t_config));
	if (!config)
		return (config);
	pthread_mutex_init(&config->print, NULL);
	pthread_mutex_init(&config->dead, NULL);
	return (config);
}


void *thread_checker(void *conf)
{
	int				i;
	t_philo			*philo;
	struct timeval	date_now;
	int				diff;
	t_config		*config;

	i = 0;
	config = (t_config *) conf;
	while (1)
	{
		gettimeofday(&date_now, NULL);
		while (i < config->num_philos)
		{
			philo = config->philos[i];
			// printf("diff : %lld\n",(to_ms(date_now) - to_ms(philo->last_eaten)));
			pthread_mutex_lock(&philo->mut_last_eaten);
			diff = to_ms(date_now) - to_ms(philo->last_eaten);
			pthread_mutex_unlock(&philo->mut_last_eaten);
			
			if ((diff > 0) && diff > config->time_die){
				
				pthread_mutex_lock(&config->dead);
				config->died = 1;
				// printf("PHILO %d HAS DIED !!!!\n", philo->num);
				// pthread_mutex_unlock(&config->print);
				print_log(philo, "has died");
				// pthread_mutex_unlock(&config->dead);
				pthread_mutex_lock(&config->print);
				printf("diff : %d\n",(diff));
				return NULL;
				// printf("last eaten : %lld\n",to_ms(philo->last_eaten));
				// printf("now : %lld\n",to_ms(date_now));
				ft_usleep(200000);
			}
			i++;
		}
		if(i >= config->num_philos)
			i = 0;
		
	}
	return (NULL);
	
}


void join_thread_watcher(t_config *config)
{
	pthread_t monitor;

	pthread_create(&monitor, NULL, &thread_checker, config);
	pthread_join(monitor, NULL);
}

int main(int argc, char **av)
{
	t_config *config;
	
	config = init_config();
	
	if (argc >=4)
	{
		parse_args(av, config);
		validate_args(config);
		create_philos(config);
	}
	else
		printf("You must give minimum of args\n");
}