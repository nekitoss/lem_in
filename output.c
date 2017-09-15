/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:29:40 by nekitoss          #+#    #+#             */
/*   Updated: 2017/09/15 16:29:41 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

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

void				direct_connection(t_lemin *ls)
{
	size_t	i;

	i = 1;
	printf("\n");
	while (i < ls->ant_num + 1)
	{
		printf("L%zu-%s ", i, ls->end_room_ptr->name);
		i++;
	}
	printf("\n");
}

void				print_result(t_lemin *ls)
{
	size_t	i;
	size_t	st_num;

	ls->names = (char **)ft_memalloc(sizeof(char *) * (ls->shortest_way + 2));
	i = 0;
	while (i < ls->shortest_way + 1)
	{
		(ls->names)[i] = find_room_name_by_number(ls, (ls->fin_slv)[i]);
		i++;
	}
	st_num = 0;
	printf("\n");
	while (st_num <= ls->ant_num + ls->shortest_way)
	{
		i = 1;
		while (i <= ls->shortest_way && i <= st_num)
		{
			if (st_num - i < ls->ant_num)
				printf("L%zu-%s ", st_num - i + 1, (ls->names)[i]);
			i++;
		}
		printf("\n");
		st_num++;
	}
}
