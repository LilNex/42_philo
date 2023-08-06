/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:52:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/06 17:30:22 by ichaiq           ###   ########.fr       */
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


void thread_checker(t_config *conf)
{
	int	i;
	t_philo *philo;
	struct timeval date_now;

	i = 0;
	while (1)
	{
		gettimeofday(&date_now, NULL);
		while (i < conf->num_philos)
		{
			philo = conf->philos[i];
			// printf("diff : %lld\n",(to_ms(date_now) - to_ms(philo->last_eaten)));
			pthread_mutex_lock(&philo->mut_last_eaten);
			int diff = to_ms(date_now) - to_ms(philo->last_eaten);
			pthread_mutex_unlock(&philo->mut_last_eaten);
			
			if ((diff > 0) && diff > conf->time_die){
				
				pthread_mutex_lock(&conf->dead);
				// pthread_mutex_lock(&conf->print);
				conf->died = 1;
				// printf("PHILO %d HAS DIED !!!!\n", philo->num);
				// pthread_mutex_unlock(&conf->print);
				print_log(philo, "has died");
				// pthread_mutex_unlock(&conf->dead);
				printf("diff : %d\n",(diff));
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