/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_lem2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:11:59 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/03 17:12:01 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		del_lems(t_data *data, t_lem *lems[data->ant_count])
{
	int	i;

	i = 0;
	while (i < data->ant_count)
	{
		free(lems[i++]);
	}
	return (1);
}

int		add_lem(t_data *data, int i, t_lem *lems[data->ant_count], int cur_lems)
{
	t_lem *new;

	new = (t_lem*)malloc(sizeof(t_lem));
	new->road = data->roads[i];
	new->n = cur_lems + 1;
	new->finished = 0;
	lems[cur_lems] = new;
	data->col--;
	data->cur_n++;
	return (++cur_lems);
}
