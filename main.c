#include "ft_lem_in.h"

/*
новая строка - конец ввода
нет старта или енда, несоотвествие паттерну муравь и порядку (число, команты, нет\не ноль муравьев)?, не минус муравьев- еррор
неизвестная команда
две решетки - команда, одна решетка - комент
связь между стартоми концом, существование обоих
после старта или энда должна идти комната
название комнаты не L #
два пробела, только цифры в числах
не может быть две комнаты с одинаковым именем
старт-конец - все сразу за один ход


бонусы%
ERROR: errormsg
цвета

матрица смежности
*/

#define RAW_D (ls->raw)
#define ROOM (ls->rooms)
#define NO_LINK 0
#define LINKED 1
#define BLOCKED 3

#define ARRAY_TYPE size_t

typedef struct 		s_path
{
	size_t			lenth;
	size_t			*solv;
	struct s_path	*next;
}					t_path;

typedef struct 		s_indata
{
	char			*str;
	struct s_indata	*next;
}					t_indata;

typedef struct		s_room
{
	char			*name;
	size_t			num;
	struct s_room	*next;
}					t_room;

typedef struct		s_lemin
{
	size_t			ant_num;
	t_room			*rooms;
	t_indata		*raw;
	size_t			start_room;
	size_t			end_room;
	t_room			*start_room_ptr;
	t_room			*end_room_ptr;
	int				**dep_matr;
	ARRAY_TYPE		*temp_solv;
	size_t			room_quantity;
	size_t			shortest_way;
	ARRAY_TYPE		*final_solv;
	char			**names;
}					t_lemin;

void				my_error(char *str1, char *str2)//, t_lemin *ls)
{
	printf("%sERROR:%s%s%s\n", "\033[01;31m" ,str1, str2, "\033[0m");
	//freestructure
	// ls = NULL;
	exit (1);
}

void				add_data(t_indata **head, char *str)
{
	t_indata *tmp;

	tmp = *head;
	if (tmp == NULL)
	{
		// *head = (t_indata *)malloc(sizeof(t_indata));
		// ft_bzero((*head), sizeof(t_indata));
		*head = (t_indata *)ft_memalloc(sizeof(t_indata));
		// // *head = (t_indata *)malloc(sizeof(t_indata));
		// (*head)->next = NULL;
		(*head)->str = (str);
	}
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		// tmp->next = (t_indata *)malloc(sizeof(t_indata));
		// ft_bzero((tmp->next), sizeof(t_indata));
		tmp->next = (t_indata *)ft_memalloc(sizeof(t_indata));
		// // tmp->next = (t_indata *)malloc(sizeof(t_indata));
		tmp->next->str = (str);
		// tmp->next->next = NULL;
	}
}

t_room				*add_room(t_room **head, char *str)
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
		while(tmp->next)
		{
			if (ft_strequ(tmp_name, tmp->name))
				my_error("room already exist: ", str);
			tmp = tmp->next;
		}
		if (ft_strequ(tmp_name, tmp->name))
				my_error("room already exist: ", str);
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

int					is_room(char *str)
{
	char **tmp;

	if (is_good_name(str))
	{
		if (ft_cntchr(str, ' ') == 2)
		{
			tmp = ft_strsplit(str, ' ');
			if (!(ft_is_number(tmp[1], 0, -1)) || !(ft_is_number(tmp[2], 0, -1)))
			{
				my_error("room coordinate is not a number: ", (!(ft_is_number(tmp[1], 0, -1)) ? tmp[1] : tmp[2]));
				return (0);
			}
		}
		else
		{
			if (is_link(str))
				return (0);
			my_error("incorrect room format: ", str);
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
		if ((is_command(tmp->str) && ((ft_strcmp(tmp->str, "##start") && ft_strcmp(tmp->str, "##end")))) || (is_comment(tmp->str)))
		{
			tmp = tmp->next;
			continue ;
		}
		if (!(ft_is_number(tmp->str, 0, -1)))
			my_error("Wrong line instead ant number: ", tmp->str);
		ant_tmp = ft_atoi(tmp->str);
		if (ant_tmp < 1)
			my_error("Wrong number of ants: ", tmp->str);
		ls->ant_num = (size_t)ant_tmp;
		tmp = tmp->next;
		return (tmp);
	}
	my_error("no rows!", "");
	return (NULL);
}

void				read_end_start_room(t_lemin *ls, t_indata **tmp, int start)
{
	if ((*tmp)->next)
	{
		*tmp = (*tmp)->next;
		// while ((*tmp) && is_comment((*tmp)->str))
		// 	*tmp = (*tmp)->next;
		if (is_room((*tmp)->str))
		{
			// ls->start_room = counter;
			if (start)
			{	
				if (ls->start_room_ptr)
					my_error("start command repeats", "");
				ls->start_room_ptr = add_room(&(ls->rooms), (*tmp)->str);
			}
			else
			{
				if (ls->end_room_ptr)
					my_error("end command repeats", "");
				ls->end_room_ptr = add_room(&(ls->rooms), (*tmp)->str);
			}
			return ;
		}
	}
	if (start)
		my_error("no correct room after start command, instead got: ", (*tmp)->str);
	else
		my_error("no correct room after end command, instead got: ", (*tmp)->str);
}

void				print_rooms(t_lemin *ls)
{
	t_room *tmp;

	tmp = ls->rooms;
	printf("ROOM_LIST:\n");
	while (tmp)
	{
		printf("%zu; %s\n", tmp->num, tmp->name);
		tmp = tmp->next;
	}
	printf("END_ROOM_LIST;\n");
}

void				print_dep_matrix(t_lemin *ls)
{
	size_t	i;
	size_t	j;

	i = 0;
	printf("DEPENDANCE_MATRIX:\n");
	while (i < ls->room_quantity)
	{
		j = 0;
		while (j < ls->room_quantity)
		{
			printf("% 2d", ls->dep_matr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("END_DEPENDANCE_MATRIX;\n");
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
//printf("\nSTART PARSING\n");
	tmp = find_ant_num(RAW_D, ls);
	if (!tmp)
		my_error("no rooms found after ant number", "");
	while (tmp)
	{
		if (!(is_comment(tmp->str)))
		{
			if (!(is_command(tmp->str)))
			{
				if ((is_room(tmp->str)))
				{
					add_room(&(ls->rooms), tmp->str);
				}
				else if ((is_link(tmp->str)))
				{
					//printf("REACHED LINKS\n");
					return (tmp);
				}
				else
				{
					my_error("Wrong link, or no links found after room: ", tmp->str);
				}
			}
			else
			{
				if (tmp->next != NULL)
				{
					if (ft_strcmp(tmp->str, "##start") == 0)
					{
						//printf("found start command\n");
						read_end_start_room(ls, &tmp, 1);
						//printf("start room ptr:%p\n", ls->start_room_ptr);
					}
					else if (ft_strcmp(tmp->str, "##end") == 0)
					{
						//printf("found end command\n");
						read_end_start_room(ls, &tmp, 0);
						//printf("start room ptr:%p\n", ls->end_room_ptr);
						//read_end_room(ls, &tmp);
					}
					//else
					//{
					//	printf("command, but not a start/end\n");
					//}
				}
				// else
				// 	printf("found command, but reached end of list\n");

			}
			// if (*start = *end)
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
	my_error("wrong link - no room with such name: ", str);
	return (0);
}

void				parse_links(t_lemin *ls, t_indata *tmp)
{
	char	**arr;
	size_t	n1;
	size_t	n2;

	if (tmp == NULL)
		my_error("no links found!", "");
	ls->dep_matr = ft_newarrint(ls->room_quantity, ls->room_quantity);
	while (tmp)
	{
		if (is_link(tmp->str))
		{
			arr = ft_strsplit(tmp->str, '-');
			n1 = find_room_number_by_name(ls, arr[0]);
			n2 = find_room_number_by_name(ls, arr[1]);
			if (n1 != n2)
			{
			//printf("%zu(%s)-->%zu(%s)\n", n1, arr[0], n2, arr[1]);
			ls->dep_matr[n1][n2] = LINKED;
			ls->dep_matr[n2][n1] = LINKED;
			}
		}
		else if (!(is_command(tmp->str) && (ft_strcmp(tmp->str, "##start") && ft_strcmp(tmp->str, "##end"))) && !(is_comment(tmp->str)))
			my_error("wronk link format: ", tmp->str);
		tmp = tmp->next;
	}
}

int					seen_before(t_lemin *ls, size_t *depth, size_t row_to_check)
{
	size_t i;

	i = 0;
	while (i < (*depth))
	{
		if  ((ls->temp_solv)[i] == row_to_check)
			return (1);
		i++;
	}
	return (0);
}
// size_t cnt = 0;

void					find_shortest_way(t_lemin *ls, size_t row, size_t *depth)
{
	size_t	j;
	
// print_dep_matrix(ls);
	if ((*depth) > ls->shortest_way)
		return ;
	if (row == ls->end_room && (*depth) < ls->shortest_way)
	{
		// cnt++;
		(ls->temp_solv)[(*depth)] = row;
		ls->shortest_way = *depth;
		// printf("\n%zu\n", *depth);
		// zz = 0;

		// while (zz < *depth)
		// {
		// 	ls->final_solv[zz] = ls->temp_solv[zz];
		// 	zz++;
		// }
		// printf("\ndepth=%zu\n", *depth);
		// for (unsigned int z = 0; z <= (*depth); z++)
		// {
		// 	ls->final_solv[z] = ls->temp_solv[z];
		// 	// printf(" %2zu", (ls->temp_solv)[z]);
		// }
		// printf("\n");
		//memcpy(&(ls->shortest_way), depth, sizeof(ARRAY_TYPE));
		//printf("shortest = %zu\n", ls->shortest_way);
		ft_memcpy(ls->final_solv, ls->temp_solv, sizeof(ARRAY_TYPE) * (*depth + 1));
		// ls->shortest_way = (*depth);
		return ;
	}
	// cnt++;
	// if ((*depth) > ls->room_quantity + 1)
	// 	my_error("recursion gone to deep in you", "");
	j = 0;
	while (j < ls->room_quantity)
	{
		// if (row != j && ls->dep_matr[row][j] == LINKED && !seen_before(ls, depth, j))
		if (ls->dep_matr[row][j] == LINKED && !seen_before(ls, depth, j))
		{
			(ls->temp_solv)[(*depth)] = row;
			(*depth)++;
			find_shortest_way(ls, j, depth);
			(*depth)--;
		}
		j++;
	}
}

void				direct_connection()
{
	my_error("DIRECT_CONNECTION_UNFINISHED", " FINISH_HIM");
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
	my_error("internal:", "no name with such number");
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
		(ls->names)[i] = find_room_name_by_number(ls, (ls->final_solv)[i]);
		i++;
	}
	i = 0;
	st_num = 0
	printf("\n");
	while (st_num <= ls->ant_num + ls->shortest_way)
	{
		i = 0;
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
	char	*buf;
	size_t	depth;

	depth = 0;
	while(get_next_line(0, &buf) && *buf != '\0')
		add_data(&RAW_D, buf);
	if (!(ls->raw) || (ls->raw->str)[0] == '\0')
		my_error("empty input ", "or file starts with empty line!");
	// ft_strdel(&buf); //низя стрдел, указатель одинаков с последним стрингом индаты
	print_indata(ls);
	t_indata *process = parse_ant_and_rooms(ls);
	if (!(ls->start_room_ptr))
		my_error("no start command found!", "");
	if (!(ls->end_room_ptr))
		my_error("no end command found!", "");
	numerate_rooms(ls, ls->rooms);
	//print_rooms(ls);
	parse_links(ls, process);
	// print_dep_matrix(ls);
	if (ls->dep_matr[ls->start_room][ls->end_room] == LINKED)
		direct_connection();
	else
	{
		ls->temp_solv = (ARRAY_TYPE *)ft_memalloc(sizeof(ARRAY_TYPE) * ls->room_quantity + 1);
		ls->final_solv = (ARRAY_TYPE *)ft_memalloc(sizeof(ARRAY_TYPE) * ls->room_quantity + 1);
		ls->shortest_way = ULONG_MAX;
		find_shortest_way(ls, ls->start_room, &depth);
		if (ls->shortest_way == ULONG_MAX)
			my_error("start and end are not connected", "");
		// printf("shortest len=%zu\n", ls->shortest_way);
		print_result(ls);
	}
	// printf("cnt = %zu\n", cnt);
	for (size_t z = 0; z <= ls->shortest_way; z++)
			printf("-%s-", (ls->names)[z]);
	printf("\n");

}

int					main(void)
{
	t_lemin	*ls;

	ls = ft_memalloc(sizeof(t_lemin));
	read_input(ls);
	return (0);
}
