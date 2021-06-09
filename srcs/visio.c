#include "lemin.h"

void	ft_draw_point(t_fdf *fdf, t_point p, int color)
{
	int	i;

	if (p.x >= 0 && p.x < WIN_WIDTH && p.y >= 0 && p.y < WIN_HEIGHT)
	{
		i = (p.x * fdf->bits_per_pixel / 8) + (p.y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
	}
}

t_point	ft_iso(t_map *map, t_point p)
{
	int		x_old;
	int		y_old;

	p.x *= map->scale;
	p.y *= map->scale;
	/*p.z *= map->scale;
	if (map->z != 0)
		p.z /= map->z;*/
	p.x += map->sd_x;
	p.y += map->sd_y;
	//p.x -= (map->x * map->scale) / 2;
	//p.y -= (map->y * map->scale) / 2;
	x_old = p.x;
	y_old = p.y;
	p.x = (x_old - y_old) * cos(0.523599);
	p.y = /*-p.z + */(x_old + y_old) * sin(0.523599);
	//p.x += (WIN_WIDTH + map->x * map->scale) / 4;
	//p.y += (WIN_HEIGHT + map->y * map->scale) / 4;
	return (p);
}

void	ft_draw_line(t_fdf *fdf, t_point p_1, t_point p_2)
{
	t_point	delta;
	t_point	sign;
	t_point	curr;
	int		error[2];

	delta.x = p_1.x > p_2.x ? p_1.x - p_2.x : p_2.x - p_1.x;
	delta.y = p_1.y > p_2.y ? p_1.y - p_2.y : p_2.y - p_1.y;
	sign.x = p_1.x < p_2.x ? 1 : -1;
	sign.y = p_1.y < p_2.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	curr = p_1;
	while (curr.x != p_2.x || curr.y != p_2.y)
	{
		ft_draw_point(fdf, curr, LINE_COLOR);
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			curr.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			curr.y += sign.y;
		}
	}
}

void	ft_draw_graf(t_fdf *fdf, t_map *map, t_data *data)
{
	t_node	*cur;
	t_node	*cur_rel;
	char	**buf;
	int		i;
	t_point	coord[2];

	cur = *data->nodes;
	while (cur != NULL)
	{
		buf = ft_strsplit(cur->rel, ' ');
		i = 0;
		coord[0].x = cur->x;
		coord[0].y = cur->y;
		while (buf[i])
		{
			cur_rel = ft_search(buf[i], data->nodes);
			coord[1].x = cur_rel->x;
			coord[1].y = cur_rel->y;
			ft_draw_line(fdf, ft_iso(map, coord[0]), ft_iso(map, coord[1]));
		}
		cur = cur->next;
	}
}

void	ft_draw_map(t_fdf *fdf, t_data *data)
{
	t_point	p;
	int		*img;
	int		i;

	ft_bzero(fdf->data_addr,
	WIN_WIDTH * WIN_HEIGHT * (fdf->bits_per_pixel / 8));
	p.x = WIN_WIDTH / 2;
	p.y = WIN_HEIGHT / 2;
	img = (int*)fdf->data_addr;
	i = -1;
	while (++i < WIN_WIDTH * WIN_HEIGHT)
		img[i] = BACKGROUND_COLOR;
	ft_draw_graf(fdf, fdf->map, data);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
}

t_fdf	*ft_init_fdf(char *title, t_map *map)
{
	t_fdf	*fdf;

	if (!(fdf = (t_fdf*)ft_memalloc(sizeof(t_fdf))))
		ft_error("FdF initialization error");
	if (!(fdf->mlx = mlx_init()))
		ft_error("Mlx initialization error");
	if (!(fdf->window = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, title)))
		ft_error("New window initialization error");
	if (!(fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT)))
		ft_error("New image initialization error");
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
										&(fdf->size_line), &(fdf->end));
	fdf->map = map;
	return (fdf);
}
/*
void	ft_redraw_map(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	if (!(fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT)))
	{
		(void)fdf;
		ft_error("New image initialization error");
	}
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
										&(fdf->size_line), &(fdf->end));
	ft_draw_map(fdf);
}
*/
t_map	*ft_init_map(t_data *data)
{
	t_map	*map;
	t_point	min;
	t_point max;
	t_node	*buf;

	map = ft_memalloc(sizeof(t_map));
	buf = *data->nodes;
	min.x = INT_MAX;
	min.y = INT_MAX;
	max.x = INT_MIN;
	max.y = INT_MIN;
	while (buf != NULL)
	{
		if (buf->x < min.x)
			min.x = buf->x;
		if (buf->y < min.y)
			min.y = buf->y;		
		if (buf->x > max.x)
			max.x = buf->x;
		if (buf->y > max.y)
			max.y = buf->y;
		buf = buf->next;
	}
	map->delta_x = max.x - min.x;
	map->delta_y = max.y - min.y;
	if (WIN_WIDTH / (2 * map->delta_y) < WIN_HEIGHT / (2 * map->delta_x))
		map->scale = WIN_WIDTH / map->delta_y;
	else
		map->scale = WIN_HEIGHT / map->delta_x;
	map->sd_x = 0;
	map->sd_y = 0;
	return (map);
}

int		visio(t_data *data)
{
	t_fdf	*fdf;
	t_map	*map;

	map = ft_init_map(data);
	fdf = ft_init_fdf("lem in visio", map);
	ft_draw_map(fdf, data);
	/*mlx_key_hook(fdf->window, ft_key_hook, fdf);
	mlx_loop(fdf->mlx);*/
	return (1);
}
