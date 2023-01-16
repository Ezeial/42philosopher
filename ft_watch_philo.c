#include "philosophers.h"

void ft_watch_philo(t_table *table)
{
    int i;
    int satiated_philos;

    if (!table->input_data.nb_of_philos)
        return ;
    while (42)
    {
        i = 0;
        while (i < table->input_data.nb_of_philos)
        {
            pthread_mutex_lock(&(table->meal_mutex));
            if (ft_timestamp() - table->philos[i].last_meal >= (unsigned long)table->input_data.time_to_die)
            {
                pthread_mutex_unlock(&(table->meal_mutex));
                pthread_mutex_lock(&(table->death_mutex));
                table->is_dead = 1;
                pthread_mutex_unlock(&(table->death_mutex));
                ft_print(&(table->philos[i]), DYING);
                return ;
            }
            pthread_mutex_unlock(&(table->meal_mutex));
            i++;
        }
        if (table->input_data.must_eat >= 0)
        {
            pthread_mutex_lock(&(table->satiated_mutex));
            satiated_philos = table->satiated_philos;
            pthread_mutex_unlock(&(table->satiated_mutex));
            if (satiated_philos == table->input_data.nb_of_philos)
                return ;
        }
    }
}