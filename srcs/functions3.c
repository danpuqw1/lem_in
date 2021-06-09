/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:07:38 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/03 17:07:41 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			ft_roaddelone(t_road **alst)
{
	t_road *new_l;

	new_l = *alst;
	if (new_l)
	{
		free(new_l->edge);
		free(*alst);
		*alst = NULL;
	}
}

void			ft_roaddel(t_road **alst)
{
	t_road **buf;

	buf = alst;
	if (buf)
	{
		while ((*buf)->next)
			ft_roaddel(&(*buf)->next);
		ft_roaddelone(&(*buf));
	}
}

int				error_check(t_data *all)
{
	if (all == NULL || all->ant_count == 0)
		return (1);
	if (all->start == NULL || all->end == NULL)
		return (1);
	if (all->start->rel == NULL || all->end->rel == NULL)
		return (1);
	if (all->invalid == 1)
		return (1);
	return (0);
}
