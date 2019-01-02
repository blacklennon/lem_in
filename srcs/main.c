/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 19:11:46 by llopez            #+#    #+#             */
/*   Updated: 2018/12/18 15:52:52 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	bonus_manager(int argc, char **argv, t_infos *infos)
{
	int	i;

	i = 0;
	infos->select = -1;
	infos->bonus = 0;
	while (argc > i)
	{
		if (!ft_strcmp(argv[i], "-colors"))
			infos->bonus = 1;
		if (!ft_strcmp(argv[i], "-select") && argv[i + 1])
			infos->select = ft_atoi(argv[i + 1]);
		if (!ft_strcmp(argv[i], "-ants") && argv[i + 1])
			infos->bonusants = ft_atoi(argv[i + 1]);
		i++;
	}
}

int				main(int argc, char **argv)
{
	t_tube		*room_list;
	t_infos		*infos;

	if (!(infos = (t_infos *)malloc(sizeof(t_infos))))
		return (EXIT_FAILURE);
	room_list = NULL;
	set_infos(infos);
	bonus_manager(argc, argv, infos);
	read_stdin(&room_list, infos);
	if (!room_list || !infos->start || !infos->end || infos->fourmis <= 0)
		display_error(room_list, infos);
	else
		set_research(infos, room_list);
	free_everything(room_list, infos);
	return (EXIT_SUCCESS);
}
