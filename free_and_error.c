/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:18:15 by nekitoss          #+#    #+#             */
/*   Updated: 2017/09/15 16:18:18 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
