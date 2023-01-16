#include "philosophers.h"

static int  ft_init_forks(t_table *table)
{
    int i;
    int j;

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

int ft_init(t_table *table)
{
    int i;

    table->is_dead = 0;
    table->satiated_philos = 0;
    table->philos = malloc(sizeof(t_philo) * table->input_data.nb_of_philos);
    if (table->philos == NULL)
        return (-1);
    i = 0;
    while (i < table->input_data.nb_of_philos)
    {
        table->philos[i].nb = i + 1;
        table->philos[i].has_eaten = 0;
        table->philos[i].last_meal = 0;
        table->philos[i].table = table;
        i++;
    }
    if (ft_init_forks(table) < 0)
    {
        free(table->philos);
        return (-1);
    }
    if (pthread_mutex_init(&(table->print_mutex), NULL) < 0
            || pthread_mutex_init(&(table->meal_mutex), NULL) < 0
            || pthread_mutex_init(&(table->death_mutex), NULL) < 0
            || pthread_mutex_init(&(table->satiated_mutex), NULL) < 0)
    {
        ft_destroy_forks(table);
        free(table->philos);
        return (-1);
    }
    return (0);
}