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