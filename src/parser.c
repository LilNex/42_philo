/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:53:25 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/12 05:24:46 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	validate_param(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	validate_args(t_config *config)
{
	if (config->time_die <= 60 || config->time_eat <= 60
		|| config->time_sleep <= 60)
		return (ft_exit("Time shouldn't be less than 60ms\n"),0);
	return (1);
}

void	parse_args(char **args, t_config *config)
{
	int	i;

	i = 1;
	while (args[i])
		if (!validate_param(args[i++]))
			return ;
	config->num_philos = ft_atoi(args[1]);
	config->time_die = ft_atoi(args[2]);
	config->time_eat = ft_atoi(args[3]);
	config->time_sleep = ft_atoi(args[4]);
}
