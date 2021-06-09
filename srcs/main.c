/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:13:14 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/05 18:13:15 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <fcntl.h>

void	print_map(t_data *all)
{
	int i;

	i = 0;
	while (i < all->lines_count)
	{
		ft_putstr(all->lines[i]);
		ft_putchar('\n');
		i++;
	}
}

void	find_roads(t_data *all)
{
	int i;
	int j;
	int res;

	i = 0;
	j = 0;
	res = 1;
	while (res != 0)
	{
		res = bfs(all, i, j);
		j++;
		i += 3;
	}
}

void	error_clear(t_data *all)
{
	if (all != NULL)
		ft_datadel(all);
	ft_error("ERROR");
}

void	print_roads(t_data *all)
{
	int		i;
	t_road	*buf;

	i = 0;
	ft_putnbr(all->roads_count);
	ft_putchar('\n');
	while (i < all->roads_count)
	{
		buf = all->roads[i];
		ft_putstr("len = ");
		ft_putnbr(buf->len);
		ft_putstr(" - ");
		while (buf)
		{
			ft_putstr(buf->edge);
			ft_putchar(' ');
			buf = buf->next;
		}
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*test;
	t_data	*all;

	fd = 0;
	test = NULL;
	if (read(fd, test, 0) == -1)
		ft_error("ERROR");
	all = ft_read(fd, MAP_SIZE);
	if (error_check(all))
		error_clear(all);
	find_roads(all);
	if (all->roads_count == 0 || all->roads[0] == NULL)
		error_clear(all);
	if (argc >= 2 && ft_strcmp(argv[1], "-d") == 0)
		print_roads(all);
	if (argc >= 2 && ft_strcmp(argv[1], "-v") == 0)
		visio(all);
	print_map(all);
	go_lem(all);
	ft_datadel(all);
	return (0);
}
