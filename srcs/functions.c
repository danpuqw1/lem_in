/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:59:11 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/03 16:59:12 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			ft_delroadsnodes(t_data *data)
{
	int		i;
	t_road	*buf2;

	i = 0;
	while (i < data->roads_count)
	{
		buf2 = data->roads[i];
		ft_roaddel(&buf2);
		i++;
	}
	free(data->roads);
	i = 0;
	while (i < data->lines_count)
	{
		free(data->lines[i]);
		i++;
	}
}

void			ft_datadel(t_data *data)
{
	int		i;
	t_node	*buf;

	i = 0;
	while (i < MAP_SIZE)
	{
		if (data->nodes[i] != NULL)
		{
			buf = data->nodes[i];
			ft_nodedel(&buf);
		}
		i++;
	}
	free(data->nodes);
	ft_delroadsnodes(data);
	free(data->lines);
	free(data);
}

void			ft_add_edge(t_road **road, int num, char *edge)
{
	t_road *new;
	t_road *buf;

	if (road[num] == NULL)
	{
		new = (t_road *)ft_memalloc(sizeof(t_road));
		new->next = NULL;
		new->edge = ft_strdup(edge);
		new->len = 1;
		road[num] = new;
	}
	else
	{
		buf = road[num];
		new = (t_road *)ft_memalloc(sizeof(t_road));
		new->edge = ft_strdup(edge);
		new->len = buf->len + 1;
		new->next = buf;
		road[num] = new;
	}
}

void			ft_error(char *mes)
{
	if (mes != NULL && ft_strlen(mes) != 0)
	{
		ft_putstr(mes);
		ft_putchar('\n');
	}
	exit(1);
}

int				ft_isnumber(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
