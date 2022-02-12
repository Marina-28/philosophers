#include "philo.h"

int ft_init_mutex(t_data *data)
{
    int i;

    i = 0;
    data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
    data->numb_of_ph);
    if (data->forks == NULL)
        return (1);
    while (i < data->numb_of_ph)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    return (0);
}