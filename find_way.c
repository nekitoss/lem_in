/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:29:20 by nekitoss          #+#    #+#             */
/*   Updated: 2017/09/15 16:29:22 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

int					seen_before(t_lemin *ls, size_t *depth, size_t row_to_check)
{
	size_t i;

	i = 0;
	while (i < (*depth))
	{
		if ((ls->tmp_slv)[i] == row_to_check)
			return (1);
		i++;
	}
	return (0);
}

void				find_shortest_way(t_lemin *ls, size_t row, size_t *depth)
{
	size_t	j;

	if ((*depth) > ls->shortest_way)
		return ;
	if (row == ls->end_room)
	{
		if ((*depth) < ls->shortest_way)
		{
			(ls->tmp_slv)[(*depth)] = row;
			ls->shortest_way = *depth;
			ft_memcpy(ls->fin_slv, ls->tmp_slv, sizeof(ARR_T) * (*depth + 1));
		}
		return ;
	}
	j = 0;
	while ((++j - 1) < ls->room_quantity)
	{
		if (ls->dep_matr[row][j - 1] == LINK && !seen_before(ls, depth, j - 1))
		{
			(ls->tmp_slv)[(*depth)] = row;
			(*depth)++;
			find_shortest_way(ls, j - 1, depth);
			(*depth)--;
		}
	}
}
