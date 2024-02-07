/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:09:00 by rbarbier          #+#    #+#             */
/*   Updated: 2024/01/15 16:31:16 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(int philo, char *action, t_data *data)
{
	pthread_mutex_lock(&data->m_print);
	pthread_mutex_lock(&data->m_time);
	pthread_mutex_lock(&data->m_end);
	if (data->end == 0)
		printf("%ld %d %s\n", get_timestamp(), philo, action);
	pthread_mutex_unlock(&data->m_end);
	pthread_mutex_unlock(&data->m_time);
	pthread_mutex_unlock(&data->m_print);
}

void	ft_sleep(t_philo *philo)
{
	print_status(philo->id, "is sleeping", philo->data);
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo->id, "is thinking", philo->data);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo->id, "has taken a fork", philo->data);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo->id, "has taken a fork", philo->data);
	print_status(philo->id, "is eating", philo->data);
	pthread_mutex_lock(&philo->data->m_time);
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->data->m_time);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->num_meals++;
	if (philo->num_meals == philo->data->num_times_must_eat)
	{
		pthread_mutex_lock(&philo->data->m_done);
		philo->data->done_eating++;
		pthread_mutex_unlock(&philo->data->m_done);
		return (1);
	}
	return (0);
}

void	*routine(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat * 0.5);
	while (1)
	{
		pthread_mutex_lock(&philo->data->m_end);
		if (philo->data->end == 1)
		{
			pthread_mutex_unlock(&philo->data->m_end);
			break ;
		}
		pthread_mutex_unlock(&philo->data->m_end);
		if (eat(philo))
			break ;
		ft_sleep(philo);
	}
	return (0);
}
