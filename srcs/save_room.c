/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 22:11:45 by llopez            #+#    #+#             */
/*   Updated: 2018/11/30 08:16:56 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_tube		*parse_room(char *name, int x, int y)
{
	t_tube	*new;

	if (!(new = (t_tube *)ft_memalloc(sizeof(*new))))
		return (NULL);
	if (!(new->name = ft_strdup(name)))
	{
		ft_memdel((void **)&new);
		return (new);
	}
	new->x = x;
	new->y = y;
	new->prev = NULL;
	new->next = NULL;
	new->links = NULL;
	new->ants = 0;
	new->vu = 0;
	return (new);
}

//TODO save room in pointer pointer
void		save_room(t_tube **room_listp, t_tube *room)
{
	t_tube	*tmp;

	if (!room_listp || !(*room_listp))
		return (room);
	tmp = *room_listp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = room;
	room->prev = tmp;
	*room_listp = ;
}
