/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:39:36 by rbarbier          #+#    #+#             */
/*   Updated: 2024/01/15 17:08:49 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	finish(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(&data->m_print);
	pthread_mutex_unlock(&data->m_end);
	pthread_mutex_unlock(&data->m_done);
	pthread_mutex_unlock(&data->m_time);
	if (data->philo_num == 1)
		pthread_mutex_unlock(&data->forks[0]);
	while (++i < data->philo_num)
		pthread_join(data->philos[i].t_id, NULL);
	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_unlock(&data->forks[i]);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_end);
	pthread_mutex_destroy(&data->m_done);
	pthread_mutex_destroy(&data->m_time);
	return (1);
}

int	ate_enough(t_data *data)
{
	pthread_mutex_lock(&data->m_end);
	data->end = 1;
	pthread_mutex_unlock(&data->m_end);
	printf(" --- Everyone ate enough! ---\n");
	return (finish(data));
}

int	supervisor(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->m_done);
		if (data->done_eating == data->philo_num \
			&& data->num_times_must_eat != 0)
			return (ate_enough(data));
		pthread_mutex_unlock(&data->m_done);
		pthread_mutex_lock(&data->m_time);
		if (data->philos[i].last_meal + data->time_to_die < get_timestamp())
		{
			pthread_mutex_lock(&data->m_end);
			data->end = 1;
			pthread_mutex_unlock(&data->m_end);
			printf("%ld %d %s\n", get_timestamp(), data->philos[i].id, "died");
			return (finish(data));
		}
		pthread_mutex_unlock(&data->m_time);
		if (++i == data->philo_num)
			i = 0;
	}
	return (0);
}

int	launch_philos(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philos;
	i = -1;
	get_timestamp();
	while (++i < data->philo_num)
	{
		if (pthread_create(&(data->philos[i].t_id), NULL, \
		&routine, &(data->philos[i])) != 0)
			error_msg("issue creating threads");
	}
	return (0);
}

int	main(int argv, char **argc)
{
	t_data		data;

	if (!input_check(argv, argc))
	{
		if (!data_init(&data, argc))
		{
			philos_init(&data);
			if (!launch_philos(&data))
				supervisor(&data);
		}
		free(data.philos);
		free(data.forks);
	}
}
