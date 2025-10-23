/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:11:44 by gorg              #+#    #+#             */
/*   Updated: 2025/01/03 23:39:31 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_morethen(t_set points, t_map *map)
{
	int		p;
	int		i;
	t_color	current_color;
	int		color;

	i = 0;
	p = 2 * points.dx - points.dy;
	while (i <= points.dy)
	{
		current_color = ft_colorstep(points.start_color,
				points.end_color, points.dy, i);
		color = (current_color.r << 16) | (current_color.g << 8)
			| current_color.b;
		my_mlx_pixel_put(map->linkmlx, points.x0, points.y0, color);
		points.y0 += points.y_dir;
		if (p < 0)
			p = p + 2 * points.dx;
		else
		{
			points.x0 += points.x_dir;
			p += 2 * (points.dx - points.dy);
		}
		i++;
	}
}

static void	ft_lessthen(t_set points, t_map *map)
{
	int		p;
	int		i;
	t_color	current_color;
	int		color;

	i = 0;
	p = 2 * points.dy - points.dx;
	while (i <= points.dx)
	{
		current_color = ft_colorstep(points.start_color,
				points.end_color, points.dx, i);
		color = (current_color.r << 16)
			| (current_color.g << 8) | current_color.b;
		my_mlx_pixel_put(map->linkmlx, points.x0, points.y0, color);
		points.x0 += points.x_dir;
		if (p < 0)
			p = p + 2 * points.dy;
		else
		{
			points.y0 += points.y_dir;
			p = p + 2 * (points.dy - points.dx);
		}
		i++;
	}
}

static void	ft_moreorless(t_set points, t_map *map)
{
	if (abs(points.dx) > abs(points.dy))
		ft_lessthen(points, map);
	else
		ft_morethen(points, map);
}

static t_set	ft_pointsdir(t_set points)
{
	if (points.x1 - points.x0 > 0)
		points.x_dir = 1;
	else
		points.x_dir = -1;
	if (points.y1 - points.y0 > 0)
		points.y_dir = 1;
	else
		points.y_dir = -1;
	return (points);
}

t_set	ft_points(int x, int y, int n, t_map *map)
{
	t_set	points;

	points.x0 = ft_isox(x, y, map->linkmlx->zoom) + map->linkmlx->xoffset;
	points.y0 = ft_isoy(x, y, map->point[y][x].z, map->linkmlx)
		+ map->linkmlx->yoffset;
	points.start_color = map->point[y][x].color;
	if (n == 1)
		x++;
	if (n == 2)
		y++;
	points.x1 = ft_isox(x, y, map->linkmlx->zoom) + map->linkmlx->xoffset;
	points.y1 = ft_isoy(x, y, map->point[y][x].z, map->linkmlx)
		+ map->linkmlx->yoffset;
	points.end_color = map->point[y][x].color;
	points = ft_pointsdir(points);
	points.dx = abs(points.x1 - points.x0);
	points.dy = abs(points.y1 - points.y0);
	ft_moreorless(points, map);
	return (points);
}
