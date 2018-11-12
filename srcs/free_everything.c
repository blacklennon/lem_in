/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 07:05:15 by llopez            #+#    #+#             */
/*   Updated: 2018/11/12 07:05:45 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_everything(t_tube *tube, t_infos *infos, t_paths *paths,\
		t_tube **ants)
{
	free_list(toend(tube));
	free(infos);
	free(ants);
	free(paths->steps);
	free(paths);
}
