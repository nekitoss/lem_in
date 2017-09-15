#include "ft_lem_in.h"

int					main(void)
{
	t_lemin	*ls;

	ls = ft_memalloc(sizeof(t_lemin));
	read_input(ls);
	parse_data(ls);
	free_all_data(ls);
	ls = NULL;
	return (0);
}
