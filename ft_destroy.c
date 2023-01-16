#include "philosophers.h"

void    ft_destroy_forks(t_table *table)
{
    int i;

    i = 0;
    while (i < table->input_data.nb_of_philos)
    {
        pthread_mutex_destroy(&(table->philos[i].fork));
        i++;
    }
}

void    ft_destroy(t_table *table)
{
    ft_destroy_forks(table);
    pthread_mutex_destroy(&(table->print_mutex));
    pthread_mutex_destroy(&(table->meal_mutex));
    pthread_mutex_destroy(&(table->death_mutex));
    pthread_mutex_destroy(&(table->satiated_mutex));
    free(table->philos);
}