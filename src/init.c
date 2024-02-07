/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:56:36 by rbarbier          #+#    #+#             */
/*   Updated: 2024/01/15 17:03:50 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	data_init(t_data *data, char **argc)
{
	int	i;

	data->philo_num = ft_atoi(argc[1]);
	data->time_to_die = ft_atoi(argc[2]);
	data->time_to_eat = ft_atoi(argc[3]);
	data->time_to_sleep = ft_atoi(argc[4]);
	if (argc[5])
		data->num_times_must_eat = ft_atoi(argc[5]);
	else
		data->num_times_must_eat = 0;
	data->done_eating = 0;
	data->end = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->forks || !data->philos)
		return (error_msg("memory problem"));
	i = 0;
	while (i < data->philo_num)
		pthread_mutex_init(&(data->forks[i++]), NULL);
	pthread_mutex_init(&(data->m_done), NULL);
	pthread_mutex_init(&(data->m_print), NULL);
	pthread_mutex_init(&(data->m_end), NULL);
	pthread_mutex_init(&(data->m_time), NULL);
	return (0);
}

void	philos_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].num_meals = 0;
		data->philos[i].data = data;
		data->philos[i].last_meal = 0;
		data->philos[i].left_fork = &(data->forks[i]);
		if (data->philo_num == 1)
			data->philos[i].right_fork = data->philos[i].left_fork;
		else
		{
			if (i + 1 == data->philo_num)
				data->philos[i].right_fork = data->forks;
			else
				data->philos[i].right_fork = &(data->forks[i + 1]);
		}
		i++;
	}
}
