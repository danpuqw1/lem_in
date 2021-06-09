/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:55:17 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/05 17:55:18 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	end_path(t_data *all, int num, int res)
{
	if (res != 0)
	{
		ft_add_edge(all->roads, num, all->end->name);
		all->roads_count++;
	}
}

void	build_path(t_data *all, t_stack *edges, int num, int res)
{
	char	*node;
	t_node	*n;
	t_edge	*e;

	end_path(all, num, res);
	node = ft_strdup(all->end->name);
	while (!ft_stkempty(edges))
	{
		e = ft_stkpop(edges);
		if (!ft_strcmp(e->end, node))
		{
			free(node);
			node = ft_strdup(e->begin);
			if (ft_strcmp(node, all->start->name))
			{
				n = ft_search(node, all->nodes);
				n->exclude = 1;
			}
			ft_add_edge(all->roads, num, node);
		}
		free_edge(e);
	}
	free(node);
}

int		check_rel(t_data *all, char **buf, int count, char *node)
{
	t_edge	*e;
	t_node	*n;
	int		i;

	i = 0;
	while (buf[i] != 0)
	{
		n = ft_search(buf[i], all->nodes);
		if (n->met == count && n->exclude == 0)
		{
			ft_quinsert(&all->queue, buf[i]);
			n->met += 1;
			e = (t_edge *)ft_memalloc(sizeof(t_edge));
			e->begin = ft_strdup(node);
			e->end = ft_strdup(buf[i]);
			ft_stkpush(&all->edges, e);
			if (ft_strcmp(n->name, all->end->name) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

void	init_conteiners(t_data *all)
{
	ft_quinit(&all->queue);
	ft_stkinit(&all->edges);
	ft_quinsert(&all->queue, all->start->name);
	all->start->met += 1;
}

int		bfs(t_data *all, int count, int num)
{
	char	*node;
	char	**buf;
	int		res;
	t_node	*n;

	res = 0;
	if (short_path(all))
		return (0);
	init_conteiners(all);
	while (!ft_quempty(&all->queue))
	{
		node = ft_qupop(&all->queue);
		n = ft_search(node, all->nodes);
		n->met += 2;
		buf = ft_strsplit(n->rel, ' ');
		res += check_rel(all, buf, count, node);
		free(node);
		ft_free_str(buf);
	}
	build_path(all, &all->edges, num, res);
	return (res);
}
