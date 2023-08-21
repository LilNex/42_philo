/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:52:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/21 02:12:39 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_config	*init_config(void)
{
	t_config	*config;

	config = malloc(1 * sizeof(t_config));
	config->number_meals = -1;
	config->exit = 0;
	if (!config)
		return (config);
	pthread_mutex_init(&config->print, NULL); 
	pthread_mutex_init(&config->dead, NULL);
	return (config);
}

int	is_all_meals_eaten(t_config *config)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (config->number_meals != -1)
	{
		while (i < config->num_philos)
		{
			pthread_mutex_lock(&config->philos[i]->mut_last_eaten);
			if (config->philos[i]->meals_eaten >= config->number_meals)
				count++;
			pthread_mutex_unlock(&config->philos[i]->mut_last_eaten);
			i++;
		}
	}
	else
		return (0);
	if (count == config->num_philos)
	{
		pthread_mutex_lock(&config->dead);
		config->exit = 1;
		pthread_mutex_unlock(&config->dead);
		return (config->exit);
	}
	return (0);
}

void	*thread_checker(void *conf)
{
	int				i;
	struct timeval	date_now;
	t_config		*config;

	i = 0;
	config = (t_config *) conf;
	pthread_mutex_lock(&config->dead);
	while (1 && !is_all_meals_eaten(config) && !config->exit)
	{
		pthread_mutex_unlock(&config->dead);
		gettimeofday(&date_now, NULL);
		// pthread_mutex_unlock(&config->dead);
		while (i < config->num_philos)
			if (!routine_checker(config->philos[i++], date_now))
				config->exit = 1;
		if (i >= config->num_philos)
			i = 0;
	}
	destroy_config(config);
	return (NULL);
}

void	f(void)
{
	system("leaks philo");
}

int	main(int argc, char **av)
{
	t_config	*config;

	atexit(f);
	config = init_config();
	if (argc >= 5)
	{
		parse_args(av, config);
		if (!validate_args(config))
			return (1);
		create_philos(config);
	}
	else
		printf("You must give minimum of args\n");
	
	
	return (0);
}
