/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:09:34 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/05 18:09:36 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_data	*init_data(int size_map)
{
	t_data *data;

	data = NULL;
	data = (t_data *)ft_memalloc(sizeof(t_data));
	data->start = NULL;
	data->end = NULL;
	data->nodes = (t_node **)ft_memalloc((sizeof(t_node) * size_map));
	data->roads = (t_road **)ft_memalloc((sizeof(t_road) * size_map));
	data->lines = (char **)ft_memalloc((sizeof(char *) * size_map));
	if (data->nodes == NULL || data->roads == NULL || data->lines == NULL)
		return (NULL);
	data->roads_count = 0;
	data->ant_count = 0;
	data->lines_count = 0;
	data->check = 0;
	data->invalid = 0;
	return (data);
}

t_node	*new_node(t_data *data, char **buf)
{
	t_node *new;

	new = (t_node *)ft_memalloc(sizeof(t_node));
	if (new == NULL)
		data->check = -1;
	new->name = ft_strdup(buf[0]);
	new->x = ft_atoi(buf[1]);
	new->y = ft_atoi(buf[2]);
	new->met = 0;
	new->exclude = 0;
	new->marker = data->check;
	new->rel = NULL;
	return (new);
}

void	push_node(t_data *data, t_node *new, int id)
{
	t_node *uk;

	if (data->nodes[id] != NULL)
	{
		uk = data->nodes[id];
		while (uk->next != NULL)
			uk = uk->next;
		uk->next = new;
	}
	else
		data->nodes[id] = new;
}

void	add_start_end(t_data *data, t_node *new)
{
	if (data->check == 3)
	{
		if (data->start != NULL)
			data->check = -1;
		else
		{
			data->start = new;
			data->check = 0;
		}
	}
	else if (data->check == 4)
	{
		if (data->end != NULL)
			data->check = -1;
		else
		{
			data->end = new;
			data->check = 0;
		}
	}
}

int		check_ret(t_data *data)
{
	data->check = 0;
	return (-1);
}
