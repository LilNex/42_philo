/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:52:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/27 23:32:04 by ichaiq           ###   ########.fr       */
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
	}
	else
		printf("You must give minimum of args\n");
 

}