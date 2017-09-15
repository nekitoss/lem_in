/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:18:40 by nekitoss          #+#    #+#             */
/*   Updated: 2017/09/15 16:18:42 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

int					is_comment(char *str)
{
	if (str && *str == '#' && str[1] != '#')
		return (1);
	return (0);
}

int					is_command(char *str)
{
	if (str && *str == '#' && str[1] && str[1] == '#')
		return (1);
	return (0);
}

int					is_good_name(char *str)
{
	if (str && *str != '\0' && *str != '#' && *str != 'L')
		return (1);
	return (0);
}

int					is_link(char *str)
{
	if (ft_cntchr(str, '-') == 1)
		return (1);
	return (0);
}

int					is_room(char *str, t_lemin *ls)
{
	char **tmp;

	if (is_good_name(str))
	{
		if (ft_cntchr(str, ' ') == 2)
		{
			tmp = ft_strsplit(str, ' ');
			if (!(ft_is_number(tmp[1], 0, -1))
				|| !(ft_is_number(tmp[2], 0, -1)))
			{
				my_error("room coordinate is not a number: ",
					(!(ft_is_number(tmp[1], 0, -1)) ? tmp[1] : tmp[2]), ls);
			}
			ft_arrdel((void ***)&tmp);
		}
		else
		{
			if (is_link(str))
				return (0);
			my_error("incorrect room format: ", str, ls);
		}
		return (1);
	}
	else
		return (0);
}
