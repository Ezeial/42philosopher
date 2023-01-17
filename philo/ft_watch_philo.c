/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_watch_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:29:43 by egiraldi          #+#    #+#             */
/*   Updated: 2023/01/17 17:34:01 by egiraldi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_check_all_eaten(t_table *table)
{
	int	satiated_philos;

	if (table->input_data.must_eat >= 0)
	{
		pthread_mutex_lock(&(table->satiated_mutex));
		satiated_philos = table->satiated_philos;
		pthread_mutex_unlock(&(table->satiated_mutex));
		if (satiated_philos == table->input_data.nb_of_philos)
			return (-1);
	}
	return (0);
}

static int	ft_check_death(t_table *table, int i)
{
	pthread_mutex_lock(&(table->meal_mutex));
	if (ft_timestamp() - table->philos[i].last_meal
		>= (unsigned long)table->input_data.time_to_die)
	{
		pthread_mutex_unlock(&(table->meal_mutex));
		pthread_mutex_lock(&(table->death_mutex));
		table->is_dead = 1;
		pthread_mutex_unlock(&(table->death_mutex));
		ft_print(&(table->philos[i]), DYING);
		return (-1);
	}
	pthread_mutex_unlock(&(table->meal_mutex));
	return (0);
}

void	ft_watch_philo(t_table *table)
{
	int	i;

	if (!table->input_data.nb_of_philos)
		return ;
	while (42)
	{
		i = 0;
		while (i < table->input_data.nb_of_philos)
		{
			if (ft_check_death(table, i) < 0)
				return ;
			i++;
		}
		if (ft_check_all_eaten(table) < 0)
			return ;
	}
}
