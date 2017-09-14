#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H

# include "libft/libft.h"

# define RAW_D (ls->raw)
# define NO_LINK 0
# define LINKED 1
# define BLOCKED 3
# define ARR_T size_t

typedef struct		s_indata
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
	char			**names;
	t_room			*rooms;
	t_room			*start_room_ptr;
	t_room			*end_room_ptr;
	t_indata		*raw;
	ARR_T			*tmp_slv;
	ARR_T			*fin_slv;
	int				**dep_matr;
	size_t			ant_num;
	size_t			start_room;
	size_t			end_room;
	size_t			room_quantity;
	size_t			shortest_way;
}					t_lemin;

#endif
