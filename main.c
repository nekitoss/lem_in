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
	int				ant_num;
	t_room			*rooms;
	t_indata		*raw;
	size_t			start_room;
	size_t			end_room;
	t_room			*start_room_ptr;
	t_room			*end_room_ptr;
	int				**dep_matr;
	size_t			room_quantity;
}					t_lemin;

void				my_error( char *str)//, t_lemin *ls)
{
	printf("ERROR:%s\n", str);
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
			if (ft_strnequ(str, tmp->name, ft_strlen(tmp->name)))
				my_error("room already exist!");
			tmp = tmp->next;
		}
		if (ft_strnequ(str, tmp->name, ft_strlen(tmp->name)))
				my_error("room already exist!");
		tmp->next = (t_room *)ft_memalloc(sizeof(t_room));
		tmp = tmp->next;
	}
	tmp->name = ft_strsub(str, 0, ft_strchr(str, ' ') - str);
	return (tmp);
}

int					is_comment(char *str)
{
	if (str && *str == '#' && str[1] && str[1] != '#')
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
				my_error("room coordinate is not a number");
				return (0);
			}
		}
		else
		{
			if (is_link(str))
				return (0);
			my_error("incorrect room format");
		}
		return (1);
	}
	else
		return (0);
}

t_indata			*find_ant_num(t_indata *tmp, t_lemin *ls)
{
	while (tmp)
	{
		// printf("trying: %s\n", tmp->str);
		if (!(is_comment(tmp->str)))
		{
			if (!(ft_is_number(tmp->str, 0, -1)))
				my_error("First non-comment row is NOT a number!");
			if ((ls->ant_num = ft_atoi(tmp->str)) < 1)
				my_error("No ants or non-positive number!");
			tmp = tmp->next;
			return (tmp);
		}
		if (is_command(tmp->str))
			my_error("Command before ant number!");
		tmp = tmp->next;
	}
	my_error("no rows!");
	return (NULL);
}

void				read_end_start_room(t_lemin *ls, t_indata **tmp, int start)
{
	if ((*tmp)->next)
	{
		*tmp = (*tmp)->next;
		while ((*tmp) && is_comment((*tmp)->str))
			*tmp = (*tmp)->next;
		if (is_room((*tmp)->str))
		{
			// ls->start_room = counter;
			if (start)
			{	
				if (ls->start_room_ptr)
					my_error("start command repeats!");
				ls->start_room_ptr = add_room(&(ls->rooms), (*tmp)->str);
			}
			else
			{
				if (ls->end_room_ptr)
					my_error("end command repeats!");
				ls->end_room_ptr = add_room(&(ls->rooms), (*tmp)->str);
			}
			return ;
		}
	}
	if (start)
		my_error("no room after start command!");
	else
		my_error("no room after end command!");
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
					my_error("Wrong link, or no links found after room!");
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
				else
					printf("found command, but reached end of list\n");

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
	my_error("wrong link - no room with such name!");
	return (0);
}

void				parse_links(t_lemin *ls, t_indata *tmp)
{
	char	**arr;
	size_t	n1;
	size_t	n2;

	if (tmp == NULL)
		my_error("no links found");
	ls->dep_matr = ft_newarrint(ls->room_quantity, ls->room_quantity);
	while (tmp)
	{
		if (is_link(tmp->str))
		{
			arr = ft_strsplit(tmp->str, '-');
			n1 = find_room_number_by_name(ls, arr[0]);
			n2 = find_room_number_by_name(ls, arr[1]);
			//printf("%zu(%s)-->%zu(%s)\n", n1, arr[0], n2, arr[1]);
			ls->dep_matr[n1][n2] = LINKED;
			ls->dep_matr[n2][n1] = LINKED;
		}
		else
			my_error("wronk link format");
		tmp = tmp->next;
	}
}

void				unblock_row(t_lemin *ls, size_t row, size_t next_row)
{
	size_t i;

	i = 0;
	while (i < ls->room_quantity)
	{
		if (ls->dep_matr[row][i] == BLOCKED)
			ls->dep_matr[row][i] = LINKED;
		i++;
	}
	ls->dep_matr[next_row][row] = LINKED;
}

void				set_row_blocked(t_lemin *ls, size_t row, size_t next_row)
{
	size_t i;

	i = 0;
	while (i < ls->room_quantity)
	{
		if (ls->dep_matr[row][i] == LINKED)
			ls->dep_matr[row][i] = BLOCKED;
		i++;
	}
	ls->dep_matr[next_row][row] = BLOCKED;
}

int					find_shortest_way(t_lemin *ls, size_t row)
{
	size_t	j;
// print_dep_matrix(ls);
	j = 0;
	if (row == ls->end_room)
	{
		printf("-%zu-", row);
		return (1);
	}
	while (j < ls->room_quantity)
	{
		if (row != j && ls->dep_matr[row][j] == LINKED)
		{
			set_row_blocked(ls, row, j);
			if (!find_shortest_way(ls, j))
				unblock_row(ls, row, j);
			else
			{
				printf("-%zu-", row);
				return (1);
			}
		}
		j++;
	}
	return (0);
}

void				direct_connection()
{
	my_error("DIRECT_CONNECTION_UNFINISHED");
}

void				read_input(t_lemin *ls)
{
	char	*buf;

	while(get_next_line(0, &buf) && *buf != '\0')
		add_data(&RAW_D, buf);
	ft_strdel(&buf);
	print_indata(ls);
	t_indata *process = parse_ant_and_rooms(ls);
	if (!(ls->start_room_ptr))
		my_error("no start command found!");
	if (!(ls->end_room_ptr))
		my_error("no end command found!");
	numerate_rooms(ls, ls->rooms);
	//print_rooms(ls);
	parse_links(ls, process);
	//print_dep_matrix(ls);
	if (ls->dep_matr[ls->start_room][ls->end_room] == LINKED)
		direct_connection();
	else
	{
		if (!find_shortest_way(ls, ls->start_room))
			my_error("no way found");
	}
}

int					main(void)
{
	t_lemin	*ls;

	ls = ft_memalloc(sizeof(t_lemin));
	read_input(ls);
	return (0);
}
