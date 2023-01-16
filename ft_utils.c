#include "philosophers.h"

static unsigned long   ft_gettime_ms()
{
    t_time	current_time;

    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

unsigned long   ft_timestamp()
{
    static unsigned long	start_time;

    if (start_time == 0)
	{
		start_time = ft_gettime_ms();
		return (0);
	}
	return (ft_gettime_ms() - start_time);
}

void	ft_sleep_ms(unsigned long time)
{
	unsigned long   start;

	start = ft_gettime_ms();
	while (ft_gettime_ms() - start < time)
		usleep (500);
}

void    ft_print(t_philo *philo, t_state state)
{
    static char *messages[] = {
        "has taken a fork",
		"is sleeping",
		"is eating",
		"is thinking",
		"died"
    };

    pthread_mutex_lock(&(philo->table->print_mutex));
    pthread_mutex_lock(&(philo->table->death_mutex));
    if (!philo->table->is_dead || state == DYING)
        printf("%lu %d %s\n", ft_timestamp(), philo->nb, messages[state]);
    pthread_mutex_unlock(&(philo->table->death_mutex));
    pthread_mutex_unlock(&(philo->table->print_mutex));
}

int     ft_check_stop(t_philo *philo)
{
    int ret;

    pthread_mutex_lock(&(philo->table->death_mutex));
    ret = philo->table->is_dead;
    pthread_mutex_unlock(&(philo->table->death_mutex));
    return (ret);
}