/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:07:52 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/05 18:07:53 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	add_node(t_data *data, char *line, int size_map)
{
	t_node	*new;
	char	**buf;
	int		id;

	data->lines[data->lines_count++] = ft_strdup(line);
	buf = ft_strsplit(line, ' ');
	id = ft_hash(buf[0], size_map);
	new = new_node(data, buf);
	push_node(data, new, id);
	if (data->check == 3 || data->check == 4)
		add_start_end(data, new);
	ft_free_str(buf);
}

int		add_rel(t_data *data, char *line)
{
	char	**buf;
	t_node	*buf3;

	data->lines[data->lines_count++] = ft_strdup(line);
	buf = ft_strsplit(line, '-');
	buf3 = ft_search(buf[0], data->nodes);
	if (buf3 == NULL)
	{
		ft_free_str(buf);
		return (-1);
	}
	buf3->rel = ft_strchrjoin(buf3->rel, buf[1], ' ');
	buf3 = ft_search(buf[1], data->nodes);
	if (buf3 == NULL)
	{
		ft_free_str(buf);
		return (-1);
	}
	buf3->rel = ft_strchrjoin(buf3->rel, buf[0], ' ');
	ft_free_str(buf);
	return (0);
}

int		check_sharp(t_data *data, char *line)
{
	if (ft_strcmp("##start", line) == 0)
	{
		data->check = 3;
		data->lines[data->lines_count++] = ft_strdup(line);
	}
	else if (ft_strcmp("##end", line) == 0)
	{
		data->check = 4;
		data->lines[data->lines_count++] = ft_strdup(line);
	}
	else if (line[0] == '#')
	{
		data->lines[data->lines_count++] = ft_strdup(line);
	}
	else if (line[0] == 'L')
		return (-1);
	return (0);
}

int		check_line(t_data *data, char *line, int size_map)
{
	if (line[0] == '#' || line[0] == 'L')
		return (check_sharp(data, line));
	else if (ft_strchr(line, ' '))
	{
		add_node(data, line, size_map);
		if (data->check == -1)
			return (check_ret(data));
	}
	else if (ft_strchr(line, '-'))
		return (add_rel(data, line));
	else if (ft_strlen(line) == 0)
		return (1);
	else if (ft_isnumber(line))
	{
		data->lines[data->lines_count++] = ft_strdup(line);
		data->ant_count = ft_atoi(line);
	}
	else
	{
		data->invalid = 1;
		return (-1);
	}
	return (0);
}

t_data	*ft_read(int fd, int size_map)
{
	int		i;
	int		k;
	char	*line;
	t_data	*data;

	k = 0;
	if (!(data = init_data(size_map)))
		return (NULL);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		k = check_line(data, line, size_map);
		if (k == -1)
		{
			ft_datadel(data);
			ft_strdel(&line);
			return (NULL);
		}
		else if (k == 1)
		{
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
	return (data);
}
