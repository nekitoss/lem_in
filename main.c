#include "ft_lem_in.h"

void				free_rooms(t_room **fr_r_ptr)
{
	if (fr_r_ptr != NULL && *fr_r_ptr != NULL)
	{
		free_rooms(&((*fr_r_ptr)->next));
		ft_strdel(&((*fr_r_ptr)->name));
		ft_memdel((void **)fr_r_ptr);
	}
	return ;
}

void				free_raw(t_indata **fr_r_ptr)
{
	if (fr_r_ptr != NULL && *fr_r_ptr != NULL)
	{
		free_raw(&((*fr_r_ptr)->next));
		ft_strdel(&((*fr_r_ptr)->str));
		ft_memdel((void **)fr_r_ptr);
	}
	return ;
}

void				free_all_data(t_lemin *ls)
{
	if (ls)
	{
		ft_strdel((char **)&(ls->names));
		free_rooms(&(ls->rooms));
		ls->start_room_ptr = NULL;
		ls->end_room_ptr = NULL;
		free_raw(&(ls->raw));
		ft_strdel((char **)&(ls->tmp_slv));
		ft_strdel((char **)&(ls->fin_slv));
		ft_arrdel((void ***)&(ls->dep_matr));
		ls->ant_num = 0;
		ls->start_room = 0;
		ls->end_room = 0;
		ls->room_quantity = 0;
		ls->shortest_way = 0;
		ft_strdel((char **)&(ls));
	}
}

void				my_error(char *str1, char *str2, t_lemin *ls)
{
	printf("%sERROR:%s%s%s\n", "\033[01;31m", str1, str2, "\033[0m");
	free_all_data(ls);
	ls = NULL;
	exit(1);
}

void				add_data(t_indata **head, char *str)
{
	t_indata *tmp;

	tmp = *head;
	if (tmp == NULL)
	{
		*head = (t_indata *)ft_memalloc(sizeof(t_indata));
		(*head)->str = (str);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_indata *)ft_memalloc(sizeof(t_indata));
		tmp->next->str = (str);
	}
}

t_room				*add_room(t_room **head, char *str, t_lemin *ls)
{
	t_room	*tmp;
	char	*tmp_name;

	tmp_name = ft_strsub(str, 0, ft_strchr(str, ' ') - str);
	tmp = *head;
	if (tmp == NULL)
	{
		*head = (t_room *)ft_memalloc(sizeof(t_room));
		tmp = *head;
	}
	else
	{
		while (tmp->next)
		{
			if (ft_strequ(tmp_name, tmp->name))
				my_error("room already exist: ", str, ls);
			tmp = tmp->next;
		}
		if (ft_strequ(tmp_name, tmp->name))
			my_error("room already exist: ", str, ls);
		tmp->next = (t_room *)ft_memalloc(sizeof(t_room));
		tmp = tmp->next;
	}
	tmp->name = tmp_name;
	return (tmp);
}

int					is_comment(char *str)
{
	if (str && *str == '#' && str[1] != '#')
		return (1);
	return (0);
}

int					is_command(char *str)
{
	if (str && *str == '#' && str[1] && str[1] == '#')
		return (1);
	return (0);
}

int					is_good_name(char *str)
{
	if (str && *str != '\0' && *str != '#' && *str != 'L')
		return (1);
	return (0);
}

int					is_link(char *str)
{
	if (ft_cntchr(str, '-') == 1)
		return (1);
	return (0);
}

int					is_room(char *str, t_lemin *ls)
{
	char **tmp;

	if (is_good_name(str))
	{
		if (ft_cntchr(str, ' ') == 2)
		{
			tmp = ft_strsplit(str, ' ');
			if (!(ft_is_number(tmp[1], 0, -1))
				|| !(ft_is_number(tmp[2], 0, -1)))
			{
				my_error("room coordinate is not a number: ",
					(!(ft_is_number(tmp[1], 0, -1)) ? tmp[1] : tmp[2]), ls);
			}
			ft_arrdel((void ***)&tmp);
		}
		else
		{
			if (is_link(str))
				return (0);
			my_error("incorrect room format: ", str, ls);
		}
		return (1);
	}
	else
		return (0);
}

t_indata			*find_ant_num(t_indata *tmp, t_lemin *ls)
{
	int		ant_tmp;

	while (tmp)
	{
		if ((is_command(tmp->str) && ((ft_strcmp(tmp->str, "##start")
			&& ft_strcmp(tmp->str, "##end")))) || (is_comment(tmp->str)))
		{
			tmp = tmp->next;
			continue ;
		}
		if (!(ft_is_number(tmp->str, 0, -1)))
			my_error("Wrong line instead ant number: ", tmp->str, ls);
		ant_tmp = ft_atoi(tmp->str);
		if (ant_tmp < 1)
			my_error("Wrong number of ants: ", tmp->str, ls);
		ls->ant_num = (size_t)ant_tmp;
		tmp = tmp->next;
		return (tmp);
	}
	my_error("no rows!", "", ls);
	return (NULL);
}

void				read_end_start_room(t_lemin *ls, t_indata **tmp, int start)
{
	if ((*tmp)->next)
	{
		*tmp = (*tmp)->next;
		if (is_room((*tmp)->str, ls))
		{
			if (start)
			{
				if (ls->start_room_ptr)
					my_error("start command repeats", "", ls);
				ls->start_room_ptr = add_room(&(ls->rooms), (*tmp)->str, ls);
			}
			else
			{
				if (ls->end_room_ptr)
					my_error("end command repeats", "", ls);
				ls->end_room_ptr = add_room(&(ls->rooms), (*tmp)->str, ls);
			}
			return ;
		}
	}
	if (start)
		my_error("incorrect room after start, instead got: ", (*tmp)->str, ls);
	else
		my_error("incorrect room after end, instead got: ", (*tmp)->str, ls);
}

void				numerate_rooms(t_lemin *ls, t_room *rm)
{
	size_t	i;

	i = 0;
	while (rm)
	{
		rm->num = i;
		if (rm == ls->start_room_ptr)
			ls->start_room = i;
		if (rm == ls->end_room_ptr)
			ls->end_room = i;
		i++;
		rm = rm->next;
	}
	ls->room_quantity = i;
}

t_indata			*parse_ant_and_rooms(t_lemin *ls)
{
	t_indata *tmp;

	tmp = find_ant_num(RAW_D, ls);
	if (!tmp)
		my_error("no rooms found after ant number", "", ls);
	while (tmp)
	{
		if (!(is_comment(tmp->str)))
		{
			if (!(is_command(tmp->str)))
			{
				if ((is_room(tmp->str, ls)))
					add_room(&(ls->rooms), tmp->str, ls);
				else if ((is_link(tmp->str)))
					return (tmp);
				else
					my_error("Wrong link, or no links found: ", tmp->str, ls);
			}
			else if (tmp->next != NULL)
			{
				if (ft_strcmp(tmp->str, "##start") == 0)
					read_end_start_room(ls, &tmp, 1);
				else if (ft_strcmp(tmp->str, "##end") == 0)
					read_end_start_room(ls, &tmp, 0);
			}
		}
		tmp = tmp->next;
	}
	return (tmp);
}

void				print_indata(t_lemin *ls)
{
	t_indata *tmp;

	tmp = RAW_D;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

size_t				find_room_number_by_name(t_lemin *ls, char *str)
{
	t_room	*tmp;

	tmp = ls->rooms;
	while (tmp)
	{
		if (ft_strequ(str, tmp->name))
			return (tmp->num);
		tmp = tmp->next;
	}
	my_error("wrong link - no room with such name: ", str, ls);
	return (0);
}

void				parse_links(t_lemin *ls, t_indata *tmp)
{
	char	**arr;
	size_t	n[2];

	if (tmp == NULL)
		my_error("no links found!", "", ls);
	ls->dep_matr = ft_newarrint(ls->room_quantity, ls->room_quantity);
	while (tmp)
	{
		if (*(tmp->str) != '#' && is_link(tmp->str))
		{
			arr = ft_strsplit(tmp->str, '-');
			n[0] = find_room_number_by_name(ls, arr[0]);
			n[1] = find_room_number_by_name(ls, arr[1]);
			if (n[0] != n[1])
			{
				ls->dep_matr[n[0]][n[1]] = LINKED;
				ls->dep_matr[n[1]][n[0]] = LINKED;
			}
			ft_arrdel((void ***)&arr);
		}
		else if (!(is_command(tmp->str) && (ft_strcmp(tmp->str, "##start")
			&& ft_strcmp(tmp->str, "##end"))) && !(is_comment(tmp->str)))
			my_error("wronk link format: ", tmp->str, ls);
		tmp = tmp->next;
	}
}

int					seen_before(t_lemin *ls, size_t *depth, size_t row_to_check)
{
	size_t i;

	i = 0;
	while (i < (*depth))
	{
		if ((ls->tmp_slv)[i] == row_to_check)
			return (1);
		i++;
	}
	return (0);
}

void				find_shortest_way(t_lemin *ls, size_t row, size_t *depth)
{
	size_t	j;

	if ((*depth) > ls->shortest_way)
		return ;
	if (row == ls->end_room)
	{
		if ((*depth) < ls->shortest_way)
		{
			(ls->tmp_slv)[(*depth)] = row;
			ls->shortest_way = *depth;
			ft_memcpy(ls->fin_slv, ls->tmp_slv, sizeof(ARR_T) * (*depth + 1));
		}
		return ;
	}
	j = 0;
	while ((++j - 1) < ls->room_quantity)
	{
		if (ls->dep_matr[row][j - 1] == LINKED && !seen_before(ls, depth, j - 1))
		{
			(ls->tmp_slv)[(*depth)] = row;
			(*depth)++;
			find_shortest_way(ls, j - 1, depth);
			(*depth)--;
		}
	}
}

void				direct_connection(t_lemin *ls)
{
	size_t	i;

	i = 1;
	printf("\n");
	while (i < ls->ant_num + 1)
	{
		printf("L%zu-%s ", i, ls->end_room_ptr->name);
		i++;
	}
	printf("\n");
}

char				*find_room_name_by_number(t_lemin *ls, size_t num)
{
	t_room	*tmp;

	tmp = ls->rooms;
	while (tmp)
	{
		if (num == tmp->num)
			return (tmp->name);
		tmp = tmp->next;
	}
	my_error("internal:", "no name with such number", ls);
	return (NULL);
}

void				print_result(t_lemin *ls)
{
	size_t	i;
	size_t	st_num;

	ls->names = (char **)ft_memalloc(sizeof(char *) * (ls->shortest_way + 2));
	i = 0;
	while (i < ls->shortest_way + 1)
	{
		(ls->names)[i] = find_room_name_by_number(ls, (ls->fin_slv)[i]);
		i++;
	}
	st_num = 0;
	printf("\n");
	while (st_num <= ls->ant_num + ls->shortest_way)
	{
		i = 1;
		while (i <= ls->shortest_way && i <= st_num)
		{
			if (st_num - i < ls->ant_num)
				printf("L%zu-%s ", st_num - i + 1, (ls->names)[i]);
			i++;
		}
		printf("\n");
		st_num++;
	}
}

void				read_input(t_lemin *ls)
{
	char		*buf;

	while (get_next_line(0, &buf) && *buf != '\0')
		add_data(&RAW_D, buf);
	if (!(ls->raw) || (ls->raw->str)[0] == '\0')
		my_error("empty input ", "or file starts with empty line!", ls);
	if (*buf == '\0')
		ft_strdel(&buf);
	print_indata(ls);
}

void				parse_data(t_lemin *ls)
{
	t_indata	*process;
	size_t		depth;

	depth = 0;
	process = parse_ant_and_rooms(ls);
	if (!(ls->start_room_ptr))
		my_error("no start command found!", "", ls);
	if (!(ls->end_room_ptr))
		my_error("no end command found!", "", ls);
	numerate_rooms(ls, ls->rooms);
	parse_links(ls, process);
	if (ls->dep_matr[ls->start_room][ls->end_room] == LINKED)
		direct_connection(ls);
	else
	{
		ls->tmp_slv = ft_memalloc(sizeof(ARR_T) * ls->room_quantity + 1);
		ls->fin_slv = ft_memalloc(sizeof(ARR_T) * ls->room_quantity + 1);
		ls->shortest_way = ULONG_MAX;
		find_shortest_way(ls, ls->start_room, &depth);
		if (ls->shortest_way == ULONG_MAX)
			my_error("start and end are not connected", "", ls);
		print_result(ls);
	}
}

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
