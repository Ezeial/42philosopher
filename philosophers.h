#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct timeval t_time;

typedef enum {
    TAKING = 0,
    SLEEPING = 1,
    EATING = 2,
    THINKING = 3,
    DYING = 4
}   t_state;

typedef struct s_input_data {
    int    nb_of_philos;
    int    time_to_die;
    int    time_to_eat;
    int    time_to_sleep;
    int    must_eat;
}   t_input_data;

typedef struct  s_philo {
    int             nb;
    int             has_eaten;
	unsigned long	last_meal;
    pthread_mutex_t fork;
    pthread_t       thread_id;
    struct s_table  *table;
}   t_philo;

typedef struct  s_table {
    t_philo         *philos;
    t_input_data    input_data;
    pthread_mutex_t print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	satiated_mutex;
    int             satiated_philos;
	int				is_dead;
}   t_table;

int             ft_parse(int ac, char **av, t_input_data *input_data);

int             ft_init(t_table *table);

int	            ft_start(t_table *table);

void	        *ft_philo(void *p);

void 			ft_watch_philo(t_table *table);

void            ft_destroy_forks(t_table *table);
void            ft_destroy(t_table *table);

unsigned long   ft_timestamp();
void	        ft_sleep_ms(unsigned long time);
void            ft_print(t_philo *philo, t_state state);
int     		ft_check_stop(t_philo *philo);

#endif