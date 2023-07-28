

#ifndef PHILO_H
#define PHILO_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"


typedef struct s_config{
    int num_philos;
    int time_sleep;
    int time_eat;
    int time_think;
}           t_config;

int validate_param(char *str);
void parse_args(char **args, t_config *config);


#endif