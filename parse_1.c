/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:18:56 by nekitoss          #+#    #+#             */
/*   Updated: 2017/09/15 16:18:57 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

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
	if (ls->dep_matr[ls->start_room][ls->end_room] == LINK)
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

void				check_command(t_lemin *ls, t_indata **tmp)
{
	if (ft_strcmp((*tmp)->str, "##start") == 0)
		read_end_start_room(ls, tmp, 1);
	else if (ft_strcmp((*tmp)->str, "##end") == 0)
		read_end_start_room(ls, tmp, 0);
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
				check_command(ls, &tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}
