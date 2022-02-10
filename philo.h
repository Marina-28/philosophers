#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
    int numb_of_ph;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int numb_of_times;
}   t_data;

int	ft_parser(t_data *data, char **argv);


#endif