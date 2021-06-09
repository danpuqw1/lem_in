/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:58:39 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/05 17:58:41 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		short_path(t_data *all)
{
	char	**buf;
	int		i;
	int		res;

	i = 0;
	res = 0;
	buf = ft_strsplit(all->start->rel, ' ');
	while (buf[i] != 0)
	{
		if (ft_strcmp(buf[i], all->end->name) == 0)
		{
			ft_add_edge(all->roads, res, all->end->name);
			ft_add_edge(all->roads, res, all->start->name);
			all->roads_count++;
			res = 1;
			break ;
		}
		i++;
	}
	ft_free_str(buf);
	return (res);
}

void	free_edge(t_edge *e)
{
	free(e->end);
	e->end = NULL;
	free(e->begin);
	e->begin = NULL;
	free(e);
	e = NULL;
}
