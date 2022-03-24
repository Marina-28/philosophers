/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:47:19 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/13 18:27:07 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *s, int f, t_data *data, t_philo **philo)
{
	if (f == 1)
		free(data->forks);
	else if (f == 2)
		free(*philo);
	else if (f == 3)
		ft_free(*philo, data);
	write(1, s, ft_strlen(s));
	return (1);
}

int	the_end(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		pthread_join(philo[i].t, NULL);
		i++;
	}
	ft_free(philo, data);
	return (0);
}

int	ft_init_pthread(t_data *data, t_philo *philo)
{
	int			i;
	pthread_t	t_eat;
	pthread_t	t_dead;

	i = 0;
	data->time_of_start = ft_current_time();
	if (pthread_create(&t_dead, NULL, &ft_check_dead, (void *)philo) != 0)
		return (1);
	pthread_detach(t_dead);
	if (data->numb_of_times != -1)
	{
		if (pthread_create(&t_eat, NULL, &ft_check_eat, (void *)philo) != 0)
			return (1);
		pthread_detach(t_eat);
	}
	return (init_philo_pthread(data, philo));
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc < 5)
		return (ft_error("Too few arguments\n", 0, &data, &philo));
	else if (argc > 6)
		return (ft_error("Too many arguments\n", 0, &data, &philo));
	if (ft_parser(&data, argv) == 1)
		return (ft_error("Invalid argument\n", 0, &data, &philo));
	data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.nop);
	if (data.forks == NULL)
		return (ft_error("Malloc error\n", 0, &data, &philo));
	philo = (t_philo *)malloc(sizeof(t_philo) * data.nop);
	if (philo == NULL)
		return (ft_error("Malloc error\n", 1, &data, &philo));
	if (ft_init_mutex(&data) == 1)
		return (ft_error("Mutex error\n", 2, &data, &philo));
	ft_init_philo(&data, &philo);
	if (ft_init_pthread(&data, philo) == 1)
		return (ft_error("Pthread error\n", 3, &data, &philo));
	pthread_mutex_lock(&data.death);
	return (the_end(philo, &data));
}
