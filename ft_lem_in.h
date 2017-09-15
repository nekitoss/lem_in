#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H

# include "libft/libft.h"

# define RAW_D (ls->raw);
# define NO_LINK 0
# define LINK 1
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

void				free_rooms(t_room **fr_r_ptr);
void				free_raw(t_indata **fr_r_ptr);
void				free_all_data(t_lemin *ls);
void				my_error(char *str1, char *str2, t_lemin *ls);
void				add_data(t_indata **head, char *str);
t_room				*add_room(t_room **head, char *str, t_lemin *ls);
int					is_comment(char *str);
int					is_command(char *str);
int					is_good_name(char *str);
int					is_link(char *str);
int					is_room(char *str, t_lemin *ls);
t_indata			*find_ant_num(t_indata *tmp, t_lemin *ls);
void				read_end_start_room(t_lemin *ls, t_indata **tmp, int start);
void				numerate_rooms(t_lemin *ls, t_room *rm);
void				check_command(t_lemin *ls, t_indata **tmp);
t_indata			*parse_ant_and_rooms(t_lemin *ls);
void				print_indata(t_lemin *ls);
size_t				find_room_number_by_name(t_lemin *ls, char *str);
void				parse_links(t_lemin *ls, t_indata *tmp);
int					seen_before(t_lemin *ls, size_t *depth,
								size_t row_to_check);
void				find_shortest_way(t_lemin *ls, size_t row, size_t *depth);
void				direct_connection(t_lemin *ls);
char				*find_room_name_by_number(t_lemin *ls, size_t num);
void				print_result(t_lemin *ls);
void				read_input(t_lemin *ls);
void				parse_data(t_lemin *ls);
int					main(void);

#endif
