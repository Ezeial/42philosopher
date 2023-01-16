#include "philosophers.h"

int main(int ac, char **av)
{
    t_table table;

    if (ft_parse(ac, av, &(table.input_data)) < 0)
    {
        write(2, "Parse error\n", 12);
        return (1);
    }
    if (ft_init(&table) < 0)
    {
        write(2, "Initialization error\n", 21);
        return (1);
    }
	if (ft_start(&table) < 0)
	{
    	ft_destroy(&table);
        write(2, "Thread error\n", 13);
        return (1);
	}
    ft_destroy(&table);
    return (0);
}