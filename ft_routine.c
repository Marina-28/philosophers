#include "philo.h"

static void	*check_dead(void *void_philo)
{
	t_data			*data;
	t_philo			*philo;

	philo = (t_philo *)void_philo;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (ft_current_time() - philo->last_eat > \
		(unsigned long long)data->time_to_die)
		{
			ft_printf_log(philo, "died");
			pthread_mutex_lock(&data->printf);
			pthread_mutex_unlock(&data->somebody_died);
			return (NULL);
		}
		pthread_mutex_unlock(&data->mutex);
	}
	return (NULL);
}

void	ft_life(t_philo *philo)
{
    if (philo->num % 2 == 0 && philo->count_eat == 0)
		usleep(philo->data->numb_of_ph / 2 * philo->data->time_to_eat);
    pthread_mutex_lock(&philo->left);
	ft_printf_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right);
	ft_printf_log(philo, "has taken a fork");
	ft_printf_log(philo, "is eating");
	usleep(1000 * philo->data->time_to_eat);
	philo->count_eat++;
	philo->last_eat = ft_current_time();
	if (philo->count_eat == philo->data->numb_of_times)
		pthread_mutex_unlock(&philo->data->count_eat);
	ft_printf_log(philo, "is sleeping");
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(&philo->right);
	usleep(philo->data->time_to_sleep * 1000);
	ft_printf_log(philo, "is thinking");
}

void	*routine(void *void_philo)
{
	t_philo		*philo;
    pthread_t	dead;

	philo = (t_philo *)void_philo;
	if (pthread_create(&dead, NULL, &check_dead, void_philo) != 0)
		return (NULL);
	//detach;
	while (1)
		ft_life(philo);
	return (NULL);
}