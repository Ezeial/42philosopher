/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:02:04 by egiraldi          #+#    #+#             */
/*   Updated: 2023/01/17 17:09:41 by egiraldi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_handle_one_philo(t_philo *philo)
{
	if (philo->table->input_data.nb_of_philos == 1)
	{
		while (ft_check_stop(philo) == 0)
		{
		}
		return (-1);
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{
	int	next_philo_idx;

	next_philo_idx = philo->nb % philo->table->input_data.nb_of_philos;
	pthread_mutex_lock(&(philo->fork));
	ft_print(philo, TAKING);
	if (ft_handle_one_philo(philo) < 0)
		return (-1);
	pthread_mutex_lock(&(philo->table->philos[next_philo_idx].fork));
	ft_print(philo, TAKING);
	ft_print(philo, EATING);
	pthread_mutex_lock(&(philo->table->meal_mutex));
	philo->last_meal = ft_timestamp();
	philo->has_eaten += 1;
	pthread_mutex_unlock(&(philo->table->meal_mutex));
	ft_sleep_ms(philo->table->input_data.time_to_eat);
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(&(philo->table->philos[next_philo_idx].fork));
	if (philo->has_eaten == philo->table->input_data.must_eat)
	{
		pthread_mutex_lock(&(philo->table->satiated_mutex));
		philo->table->satiated_philos += 1;
		pthread_mutex_unlock(&(philo->table->satiated_mutex));
		return (-1);
	}
	return (0);
}

static int	ft_sleep_and_think(t_philo *philo)
{
	if (ft_check_stop(philo) > 0)
		return (-1);
	ft_print(philo, SLEEPING);
	ft_sleep_ms(philo->table->input_data.time_to_sleep);
	ft_print(philo, THINKING);
	return (0);
}

void	*ft_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (42)
	{
		if (philo->nb % 2 == 0)
		{
			if (ft_sleep_and_think(philo) < 0)
				break ;
		}
		if (ft_check_stop(philo) > 0)
			break ;
		if (ft_eat(philo) < 0)
			break ;
		if (philo->nb % 2 != 0)
		{
			if (ft_sleep_and_think(philo) < 0)
				break ;
		}
	}
	return (NULL);
}
