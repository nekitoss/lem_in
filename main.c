/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:44:36 by nekitoss          #+#    #+#             */
/*   Updated: 2017/09/15 16:44:39 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

int					main(void)
{
	t_lemin	*ls;

	ls = ft_memalloc(sizeof(t_lemin));
	read_input(ls);
	parse_data(ls);
	free_all_data(ls);
	ls = NULL;
	return (0);
}
