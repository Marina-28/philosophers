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
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_lock(&data->death);
    return (0);
}

int ft_init_philo(t_data *data, t_philo **philo1)
{
    int i;
	t_philo	*philo;

    i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->numb_of_ph);
	if (philo == NULL)
		return (1);
    while(i < data->numb_of_ph)
    {
		philo[i].num = i + 1;
		philo[i].count_eat = 0;
		philo[i].last_eat = ft_current_time();
		philo[i].data = data;
        philo[i].left = data->forks[i];
		pthread_mutex_init(&philo[i].mutex, NULL);
		if ((i + 1) == data->numb_of_ph)
            philo[i].right = data->forks[0];
		else
			philo[i].right = data->forks[i + 1];
		i++;
    }
	*philo1 = philo;
	return (0);
}

int ft_init_pthread(t_data *data, t_philo *philo)
{
    int i;

    i = 0;
    data->time_of_start = ft_current_time();
    while (i < data->numb_of_ph)
    {
        if (pthread_create(&philo[i].t, NULL, &routine, &philo[i]) != 0)
            return (1);
		pthread_detach(philo[i].t);
		i++;
    }
    return (0);
}