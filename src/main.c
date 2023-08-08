/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:52:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/08 16:33:53 by ichaiq           ###   ########.fr       */
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
	long long		current_tick;

	i = 0;
	while (1)
	{
		gettimeofday(&date_now, NULL);
		current_tick = get_current_tick();
		while (i < conf->num_philos)
		{
			philo = conf->philos[i++];
			// printf("diff : %lld\n",(to_ms(date_now) - to_ms(philo->last_eaten)));
			pthread_mutex_lock(&philo->mut_eaten);
			if (current_tick > philo->last_eaten)
			{
				
				printf("PHILO %d HAS DIED !!!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", philo->num);
				print_log(philo, "has died");
				printf("last eaten : %lld\n",philo->last_eaten);
				printf("now : %lld\n",current_tick);
				// printf("diff : %lld\n",(to_ms(date_now) - to_ms(philo->last_eaten)));
				return ;
				ft_usleep(200000);
			}
			pthread_mutex_unlock(&philo->mut_eaten);
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