/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:53:00 by egiraldi          #+#    #+#             */
/*   Updated: 2023/01/17 17:00:34 by egiraldi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_init_forks(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (i < table->input_data.nb_of_philos)
	{
		if (pthread_mutex_init(&(table->philos[i].fork), NULL) < 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&(table->philos[j].fork));
				j++;
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	ft_init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&(table->print_mutex), NULL) < 0
		|| pthread_mutex_init(&(table->meal_mutex), NULL) < 0
		|| pthread_mutex_init(&(table->death_mutex), NULL) < 0
		|| pthread_mutex_init(&(table->satiated_mutex), NULL) < 0)
		return (-1);
	return (0);
}

static void	ft_set_default_philo(t_table *table, t_philo *philo, int i)
{
	philo->nb = i + 1;
	philo->has_eaten = 0;
	philo->last_meal = 0;
	philo->table = table;
}

int	ft_init(t_table *table)
{
	int	i;

	table->is_dead = 0;
	table->satiated_philos = 0;
	table->philos = malloc(sizeof(t_philo) * table->input_data.nb_of_philos);
	if (table->philos == NULL)
		return (-1);
	i = 0;
	while (i < table->input_data.nb_of_philos)
	{
		ft_set_default_philo(table, &(table->philos[i]), i);
		i++;
	}
	if (ft_init_forks(table) < 0)
	{
		free(table->philos);
		return (-1);
	}
	if (ft_init_mutexes(table) < 0)
	{
		ft_destroy_forks(table);
		free(table->philos);
		return (-1);
	}
	return (0);
}
