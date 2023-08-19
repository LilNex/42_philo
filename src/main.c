/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:52:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/19 01:44:42 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_config	*init_config(void)
{
	t_config	*config;

	config = malloc(1 * sizeof(t_config));
	config->number_meals = -1;
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
			if (config->philos[i]->meals_eaten >= config->number_meals)
				count++;
			i++;
		}
	}
	else
		return (0);
	if (count == config->num_philos)
	{
		pthread_mutex_lock(&config->dead);
		return (1);
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
	while (1 && !is_all_meals_eaten(config))
	{
		gettimeofday(&date_now, NULL);
		while (i < config->num_philos)
		{
			routine_checker(config->philos[i], date_now);
			i++;
		}
		if (i >= config->num_philos)
			i = 0;
	}
	i = 0;
	destroy_config(config);
	// while (config->philos[i])
	// {
	// 	destroy_thread(config->philos[i]);
	// 	free(config->philos[i++]);
	// }
	return (NULL);
}

void	ft_exit(char *str)
{

	(void) str;
	// if (str)
		// ft_putstr_fd(str, 2);
	exit(0);
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
	if (argc >= 4)
	{
		parse_args(av, config);
		validate_args(config);
		create_philos(config);
		ft_exit(NULL);
	}
	else
		printf("You must give minimum of args\n");
}
