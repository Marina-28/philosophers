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
    int				numb_of_ph;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				numb_of_times;
    long long       time_of_start;
    pthread_mutex_t	*forks;
}   t_data;


typedef struct s_philo
{
    pthread_t       t;
    int             num;
	int				count_eat;
	long long		last_eat;
    pthread_mutex_t left;
    pthread_mutex_t right;
}   t_philo;

int	ft_parser(t_data *data, char **argv);
int ft_init_mutex(t_data *data);
long long	ft_current_time(void);
int ft_init_philo(t_data *data, t_philo **philo);
int ft_init_pthread(t_data *data, t_philo **philo);

#endif