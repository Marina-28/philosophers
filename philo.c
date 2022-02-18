#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_error(char *s)
{
	write(1, s, ft_strlen(s));
	return (1);
}

long long	ft_current_time(void)
{
	unsigned long long		time;
	struct timeval	current_time;
	
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_printf_log(t_philo *philo, char *s)
{
	unsigned long long	time;

	time = ft_current_time() - philo->data->time_of_start;
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %d %s\n", time, philo->num, s);
	pthread_mutex_unlock(&philo->data->print);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc < 5)
		return (ft_error("Too few arguments\n"));
	else if (argc > 6)
		return (ft_error("Too many arguments\n"));
	if (ft_parser(&data, argv) == 1)
		return (ft_error("Invalid argument\n"));
	if (ft_init_mutex(&data) == 1 || ft_init_philo(&data, &philo) == 1)
		return (ft_error("Malloc error\n"));
	if (ft_init_pthread(&data, philo) == 1)
		return (ft_error("Pthread error\n"));
	pthread_mutex_lock(&data.death);
	return (0);
}