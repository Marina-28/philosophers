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
	long long		time;
	struct timeval	current_time;
	
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
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
	return (0);
}