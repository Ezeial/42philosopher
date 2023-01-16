#include "philosophers.h"

static int ft_will_exceed(unsigned long current_nb, int next_digit)
{
    if (current_nb > INT_MAX / 10)
        return (-1);
    if (current_nb * 10 + next_digit > INT_MAX)
        return (-1);
    return (0);
}

static int ft_parse_int(char *str, int *nb)
{
    if (!str[0])
        return (-1);
    *nb = 0;
    while (*str)
    {
        if (*str < '0' || '9' < *str)
            return (-1);
        if (ft_will_exceed(*nb, *str - '0') < 0)
            return (-1);
        *nb *= 10;
        *nb += *str - '0';
        str++;
    }
    return (0);
}

int ft_parse(int ac, char **av, t_input_data *input_data)
{
    input_data->must_eat = -1;
    if (ac != 5 && ac != 6)
        return (-1);
    if (ft_parse_int(av[1], &(input_data->nb_of_philos)) < 0)
        return (-1);
    if (ft_parse_int(av[2], &(input_data->time_to_die)) < 0)
        return (-1);
    if (ft_parse_int(av[3], &(input_data->time_to_eat)) < 0)
        return (-1);
    if (ft_parse_int(av[4], &(input_data->time_to_sleep)) < 0)
        return (-1);
    if (ac == 6 && (ft_parse_int(av[5], &(input_data->must_eat)) < 0))
        return (-1);
    if (input_data->time_to_eat > input_data->time_to_die)
        input_data->time_to_eat = input_data->time_to_die;
    if (input_data->time_to_sleep > input_data->time_to_die)
        input_data->time_to_sleep = input_data->time_to_die;
    return (0);
}