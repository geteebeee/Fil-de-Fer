/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:14:50 by gorg              #+#    #+#             */
/*   Updated: 2025/01/03 23:59:10 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color	ft_colorstep(t_color start, t_color end, int steps, int current_step)
{
	t_color	result;

	if (steps == 0)
		steps = 1;
	result.r = start.r + (end.r - start.r) * current_step / steps;
	result.g = start.g + (end.g - start.g) * current_step / steps;
	result.b = start.b + (end.b - start.b) * current_step / steps;
	return (result);
}

float	ft_isox(int x, int y, float zoom)
{
	return ((x - y) * cosf(0.523599f) * zoom);
}

float	ft_isoy(int x, int y, int z, t_mlx *mlx)
{
	return (((x + y) * sinf(0.523599f) - z * mlx->z_scale) * mlx->zoom);
}

void	ft_drawer(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (x < map->x - 1)
				ft_points(x, y, 1, map);
			if (y < map->y - 1)
				ft_points(x, y, 2, map);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->linkmlx->mlx, map->linkmlx->window,
		map->linkmlx->image, 0, 0);
}

void	ft_freedom(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->point)
		{
			i = 0;
			while (i < map->y)
			{
				free(map->point[i]);
				i++;
			}
			free(map->point);
		}
		free(map);
	}
}
