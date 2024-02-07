/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:36:09 by rbarbier          #+#    #+#             */
/*   Updated: 2024/01/15 17:03:11 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h> 
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define EAT 1
# define SLEEP 2
# define DIE 3

struct	s_philo;

typedef struct s_data
{
	int				philo_num;
	time_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_must_eat;
	int				end;
	int				done_eating;
	pthread_mutex_t	m_done;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_end;
	pthread_mutex_t	m_time;
	pthread_mutex_t	one_fork;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				num_meals;
	t_data			*data;
	time_t			last_meal;
	pthread_t		t_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

int		ft_isdigit(int c);
int		error_msg(char *msg);
int		input_check(int argv, char **argc);
int		data_init(t_data *data, char **argc);
time_t	get_timestamp(void);
void	philos_init(t_data *data);
void	print_status(int philo, char *action, t_data *data);
void	*routine(void *philo);
int		ft_atoi(const char *str);
void	ft_usleep(int ms);

#endif