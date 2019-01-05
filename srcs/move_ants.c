/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:03:15 by llopez            #+#    #+#             */
/*   Updated: 2018/12/19 17:40:27 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			fill_buffer(const char *str, char *buffer, int print,\
		t_infos *infos)
{
	static size_t	index = 0;
	int				str_len;
	char			*tmp;

	if (print || infos->bonus || infos->select > 0)
	{
		if (print)
			write(1, buffer, index);
		else
			write(1, str, ft_strlen(str));
		index = 0;
		return ;
	}
	tmp = buffer + index;
	str_len = ft_strlen(str);
	if (index + str_len >= BUFFER_SIZE - 1)
	{
		write(1, buffer, index);
		index = 0;
		fill_buffer(str, buffer, 0, infos);
		return ;
	}
	ft_memcpy(tmp, str, str_len);
	index += str_len;
}

static void		show_ant(int l, t_tube *room, t_infos *infos, char *buffer)
{
	char	*tmp;

	if (!room || !infos)
		return ;
	if (infos->select == l)
		ft_printf("\033[41mL%d-%s\033[0m", l, room->name);
	else if (infos->bonus)
		ft_printf("\033[%dmL%d-%s\033[0m", l, l, room->name);
	else
	{
		tmp = ft_itoa(l);
		fill_buffer("L", buffer, 0, infos);
		fill_buffer(tmp, buffer, 0, infos);
		fill_buffer("-", buffer, 0, infos);
		fill_buffer(room->name, buffer, 0, infos);
		free(tmp);
	}
}

static int		change_room(t_infos *infos, t_tube *from, t_tube *to, char *buffer)
{
	int	init_ants;

	init_ants = from->ants;
	if (to && to->ants == -1)
	{
		to->ants = 0;
		return (0);
	}
	if (!to || (to->ants && to != infos->end))
		return (0);
	if (to == infos->end)
		infos->end->ants++;
	if (from == infos->start)
	{
		infos->start->ants--;
		init_ants = infos->fourmis - infos->start->ants;
		to->ants = init_ants;
	}
	else
	{
		to->ants = from->ants;
		from->ants = to->ants * -1;
	}
	show_ant(init_ants, to, infos, buffer);
	return (1);
}

static t_tube		*get_minus(t_tube *room, t_infos *infos)
{
	t_tube	*minus;
	t_paths	*tmp;

	if (!room)
		return (NULL);
	tmp = room->links;
	minus = NULL;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->room == infos->end)
			return (infos->end);
		if ((!minus && !tmp->room->ants && tmp->room->steps > 0)\
			 || (minus && !tmp->room->ants && tmp->room->steps > 0 && tmp->room->steps < minus->steps))
			minus = tmp->room;
		tmp = tmp->next;
	}
	return (minus);
}

void			move_ants(t_infos *infos, char *buffer)
{
	t_tube		*tmp;
	t_tube		*base;
	t_tube		*skip;
	int		moved;
	int		ret;

	moved = 0;
	base = infos->start;
	tmp = NULL;
	skip = NULL;
	while (base->prev)
		base = base->prev;
	while (infos->end->ants <= infos->fourmis)
	{
		if (!tmp)
		{
			if (moved)
			{
				fill_buffer("\n", buffer, 0, infos);
				moved = 0;
			}
			tmp = base;
		}
		if (tmp->ants && tmp != infos->end && skip != tmp)
		{
			skip = get_minus(tmp, infos);
			if ((ret = change_room(infos, tmp, skip, buffer)))
			{
				moved += ret;
				if (ret)
					fill_buffer(" ", buffer, 0, infos);
			}
		}
		tmp = tmp->next;
	}
}
