/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:52:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/21 21:41:06 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	is_exited(t_config *config)
{
	int	val;

	val = 0;
	if (pthread_mutex_lock(&config->dead))
		return (1);
	val = config->exit;
	if (pthread_mutex_unlock(&config->dead))
		return (1);
	return (val);
}

int	set_exit(t_config *config, int value)
{
	if (pthread_mutex_lock(&config->dead))
		return (1);
	config->exit = value;
	if (pthread_mutex_unlock(&config->dead))
		return (1);
	return (value);
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
		return (set_exit(config, 1));
	return (0);
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
		if (!parse_args(av, config) || !validate_args(config))
			return (free(config), 1);
		create_philos(config);
	}
	else
		printf("You must give minimum of args\n");
	return (0);
}
