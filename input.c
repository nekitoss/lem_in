/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:30:04 by nekitoss          #+#    #+#             */
/*   Updated: 2017/09/15 16:30:05 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void				read_input(t_lemin *ls)
{
	char		*buf;

	while (get_next_line(0, &buf) && *buf != '\0')
		add_data(&RAW_D, buf);
	if (!(ls->raw) || (ls->raw->str)[0] == '\0')
		my_error("empty input ", "or file starts with empty line!", ls);
	if (*buf == '\0')
		ft_strdel(&buf);
	print_indata(ls);
}

void				add_data(t_indata **head, char *str)
{
	t_indata *tmp;

	tmp = *head;
	if (tmp == NULL)
	{
		*head = (t_indata *)ft_memalloc(sizeof(t_indata));
		(*head)->str = (str);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_indata *)ft_memalloc(sizeof(t_indata));
		tmp->next->str = (str);
	}
}
