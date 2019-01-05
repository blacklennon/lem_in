/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 12:51:27 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/05 18:16:53 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* Temporary function */
static void	print_path(t_tube **path, int size)
{
	int		i;

	i = 0;
	ft_putstr("Path: ");
	while (i <= size)
	{
		ft_printf("%s ", path[i]->name);
		i++;
	}
	ft_putchar('\n');
}

static void	explore(t_tube *position, t_infos *infos, int depth, t_tube **buf)
{
	t_paths	*edges;

	buf[depth] = position;
	if (position == infos->end)
	{
		/* TODO: save path (save the buffer state) */
		print_path(buf, depth);
		return ;
	}
	edges = position->links;
	position->vu = 1;
	if (!edges || !edges->next)
		position->vu = 2;
	while (edges)
	{
		if (edges->room->vu || edges->room == position)
		{
			edges = edges->next;
			continue ;
		}
		explore(edges->room, infos, depth + 1, buf);
		edges = edges->next;
	}
	if (position->vu == 1)
		position->vu = 0;
}

void		find_paths(t_infos *infos)
{
	t_tube		**res;

	res = (t_tube**)malloc(sizeof(res) * infos->room_total);
	if (!res)
		return ;
	explore(infos->start, infos, 0, res);
	free(res);
}