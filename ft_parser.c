#include "philo.h"

static int	ft_atoi(const char *str)
{
	int	k;
	int	n;

	k = 1;
	n = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			k = k * (-1);
		str++;
	}
	while (*str == 48)
		str++;
	while (*str > 47 && *str < 58)
	{
		n = n * 10 + k * (*str - 48);
		str++;
	}
	return (n);
}

int	check_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_parser(t_data *data, char **argv)
{
	if (check_digits(argv) == 1)
		return (1);
	data->numb_of_ph = ft_atoi(argv[1]);
	if (data->numb_of_ph == 0)
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die == 0)
		return (1);
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat == 0)
		return (1);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep == 0)
		return (1);
	if (argv[5] != NULL)
	{
		data->numb_of_times = ft_atoi(argv[5]);
		if (data->numb_of_times == 0)
		return (1);
	}
	else
		data->numb_of_times = -1;
	return (0);
}