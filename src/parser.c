/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:53:25 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/17 23:53:47 by ichaiq           ###   ########.fr       */
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
	if (config->time_die < 60 || config->time_eat < 60
		|| config->time_sleep < 60)
		return (ft_exit("Time shouldn't be less than 60ms\n"),0);
	return (1);
}

int	parse_number(char *str)
{
	int		i;
	long	nbr;
	int		signe;

	i = 0;
	nbr = 0;
	signe = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + ((int)str[i] - 48);
		i++;
	}
	return (nbr);
}

void	parse_args(char **args, t_config *config)
{
	int	i;

	i = 1;
	while (args[i])
		if (!validate_param(args[i++]))
			return ;
	config->num_philos = parse_number(args[1]);
	config->time_die = parse_number(args[2]);
	config->time_eat = parse_number(args[3]);
	config->time_sleep = parse_number(args[4]);
	if (args[5] && *args[5])
		config->number_meals = parse_number(args[5]);
}
