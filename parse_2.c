/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:19:02 by nekitoss          #+#    #+#             */
/*   Updated: 2017/09/15 16:19:03 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

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
				ls->dep_matr[n[0]][n[1]] = LINK;
				ls->dep_matr[n[1]][n[0]] = LINK;
			}
			ft_arrdel((void ***)&arr);
		}
		else if (!(is_command(tmp->str) && (ft_strcmp(tmp->str, "##start")
			&& ft_strcmp(tmp->str, "##end"))) && !(is_comment(tmp->str)))
			my_error("wrong link format: ", tmp->str, ls);
		tmp = tmp->next;
	}
}
