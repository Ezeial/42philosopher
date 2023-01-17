/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:28:49 by egiraldi          #+#    #+#             */
/*   Updated: 2023/01/17 17:29:01 by egiraldi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_start(t_table *table)
{
	int	i;

	if (table->input_data.must_eat == 0)
		return (0);
	i = 0;
	while (i < table->input_data.nb_of_philos)
	{
		if (pthread_create(&(table->philos[i].thread_id), NULL,
				ft_philo, &(table->philos[i])) < 0)
			return (-1);
		i++;
	}
	ft_watch_philo(table);
	i = 0;
	while (i < table->input_data.nb_of_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}
