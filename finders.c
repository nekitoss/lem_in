/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:30:39 by nekitoss          #+#    #+#             */
/*   Updated: 2017/09/15 16:30:40 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

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
			my_error("wrong line instead ant number: ", tmp->str, ls);
		ant_tmp = ft_atoi(tmp->str);
		if (ant_tmp < 1)
			my_error("wrong number of ants: ", tmp->str, ls);
		ls->ant_num = (size_t)ant_tmp;
		tmp = tmp->next;
		return (tmp);
	}
	my_error("no rows!", "", ls);
	return (NULL);
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
