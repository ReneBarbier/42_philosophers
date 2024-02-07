/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:46:22 by rbarbier          #+#    #+#             */
/*   Updated: 2024/01/15 17:03:31 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_values(int argv, char **argc)
{
	int	i;

	i = 0;
	while (i++ < argv - 1)
		if (ft_atoi(argc[i]) == 0)
			return (error_msg("Arguments can't be 0"));
	return (0);
}

int	input_check(int argv, char **argc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argv != 6 && argv != 5)
		return (error_msg("Number of arguments invalid"));
	while (argc[++j])
	{
		while ((argc[j][i] >= '0' && argc[j][i] <= '9'))
			i++;
		if (argc[j][i] == '\0')
		{
			if (i == 0)
				return (error_msg("Empty argument found"));
			else
				i = 0;
		}
		else if (argc[j][i] == '-' && i == 0)
			return (error_msg("Negative numbers are prohibited"));
		else
			return (error_msg("Non digit character found in arguments"));
	}
	return (check_values(argv, argc));
}
