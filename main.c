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

typedef struct s_indata
{
	char		*str;
	t_indata	*next;
}				t_indata;

typedef struct	s_room
{
	char		*name;
	size_t		num;
	t_room		*next;
}				t_room;

typedef struct	s_lemin
{
	int			ant_num;
	t_room		*rooms;
	t_indata	*raw;
}				t_lemin;

void	read_input(t_lemin *ls)
{
	
}

int				main(int argc, char **argv)
{
	t_lemin	*ls;

	ls = ft_memalloc(sizeof(t_lemin));
	read_input(ls);
	return (0);
}