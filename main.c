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

t_indata			*find_ant_num(t_indata *tmp, t_lemin *ls)
{
	while (tmp)
	{
		// printf("trying: %s\n", tmp->str);
		if (!(is_comment(tmp->str)))
		{
			if (!(ft_is_number(tmp->str, 0, -1)))
				my_error("First row is NOT a number!");
			if ((ls->ant_num = ft_atoi(tmp->str)) < 1)
				my_error("No ants!");
			tmp = tmp->next;
			return (tmp);
		}
		tmp = tmp->next;
	}
	my_error("no rows!");
	return (NULL);
}

void				parse_data(t_lemin *ls)
{
	t_indata *tmp;

	tmp = find_ant_num(RAW_D, ls);
	while (tmp)
	{
		if (!(is_comment(tmp->str)))
		{
			
			
			// if (*start = *end)
		}
		tmp = tmp->next;
	}
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

void				read_input(t_lemin *ls)
{
	char	*buf;

	while(get_next_line(0, &buf) && *buf != '\0')
		add_data(&RAW_D, buf);
	print_indata(ls);
	parse_data(ls);
}

int					main(void)
{
	t_lemin	*ls;

	ls = ft_memalloc(sizeof(t_lemin));
	read_input(ls);
	return (0);
}
