/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjeana <bjeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:55:02 by bjeana            #+#    #+#             */
/*   Updated: 2022/03/20 16:24:21 by bjeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_sem1(t_data *data)
{
	sem_unlink("death");
	data->death = sem_open("death", O_CREAT | O_EXCL, 0644, 0);
	if (data->death < 0)
	{
		sem_unlink("forks");
		sem_unlink("print");
		return (1);
	}
	sem_unlink("sem");
	data->sem = sem_open("sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->sem < 0)
	{
		sem_unlink("forks");
		sem_unlink("print");
		sem_unlink("death");
		return (1);
	}
	return (0);
}

int	ft_init_sem(t_data *data)
{
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->nop);
	if (data->forks < 0)
		return (1);
	sem_unlink("print");
	data->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print < 0)
	{
		sem_unlink("forks");
		return (1);
	}
	return (ft_init_sem1(data));
}

char	*ft_name(int i)
{
	char	*ret_itoa;
	char	*name;

	ret_itoa = ft_itoa(i);
	if (ret_itoa == NULL)
		return (NULL);
	name = ft_strjoin("stop", ret_itoa);
	free(ret_itoa);
	return (name);
}

int	ft_init_philo(t_data *data, t_philo **philo)
{
	int		i;
	char	*name;

	i = 0;
	while (i < data->nop)
	{
		(*philo)[i].num = i + 1;
		(*philo)[i].count_eat = 0;
		(*philo)[i].last_eat = 0;
		name = ft_name(i);
		if (name == NULL)
			return (1);
		sem_unlink(name);
		(*philo)[i].stop = sem_open(name, O_CREAT | O_EXCL, 0644, 0);
		free(name);
		if ((*philo)[i].stop < 0)
		{
			ft_free_stop(*philo);
			return (1);
		}
		(*philo)[i].data = data;
		i++;
	}
	return (0);
}
