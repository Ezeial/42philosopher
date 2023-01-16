#include "philosophers.h"

int    ft_eat(t_philo *philo)
{
    int next_philo_idx;

    next_philo_idx = philo->nb % philo->table->input_data.nb_of_philos;
    pthread_mutex_lock(&(philo->fork));
    ft_print(philo, TAKING);
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

void	*ft_philo(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
    while (42)
    {
        if (philo->nb % 2 == 0)
        {
            if (ft_check_stop(philo) > 0)
                break ;
            ft_print(philo, SLEEPING);
            ft_sleep_ms(philo->table->input_data.time_to_sleep);
            ft_print(philo, THINKING);
        }
        if (ft_check_stop(philo) > 0)
            break ; 
        if (ft_eat(philo) < 0)
            break ;
        if (philo->nb % 2 != 0)
        {   
            if (ft_check_stop(philo) > 0)
                break ;
            ft_print(philo, SLEEPING);
            ft_sleep_ms(philo->table->input_data.time_to_sleep);
            ft_print(philo, THINKING);
        }
    }
	return (NULL);
}