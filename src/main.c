/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilnex <lilnex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:52:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/02 15:47:40 by lilnex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


int main(int argc, char **av)
{
	t_config *config;
	
	config = ft_calloc(1, sizeof(t_config));
	if (argc >=4)
	{
		parse_args(av, config);
		validate_args(config);
		create_philos(config);
	}
	else
		printf("You must give minimum of args\n");
 

}