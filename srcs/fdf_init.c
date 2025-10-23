/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:17:25 by gorg              #+#    #+#             */
/*   Updated: 2025/01/11 13:57:19 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_minmax(t_map *map, int n, float *min, float *max)
{
	int		y;
	int		x;
	float	compare;

	*min = FLT_MAX;
	*max = FLT_MIN;
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			if (n == 1)
				compare = ft_isoy(x, y, map->point[y][x].z, map->linkmlx);
			else
				compare = ft_isox(x, y, map->linkmlx->zoom);
			if (compare < *min)
				*min = compare;
			if (compare > *max)
				*max = compare;
		}
	}
	if (*min == *max)
		*max += 1.0f;
}

static void	ft_scaling(t_map *map)
{
	int	z;
	int	x;
	int	y;

	z = 0;
	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (z < map->point[y][x].z)
				z = map->point[y][x].z;
			x++;
		}
		y++;
	}
	if (z == 0)
		map->linkmlx->z_scale = 1;
	if (z <= 10)
		map->linkmlx->z_scale = 1;
	else if (z <= 100)
		map->linkmlx->z_scale = 0.75;
	else if (z > 100)
		map->linkmlx->z_scale = 0.2;
}

static void	startmlx(t_mlx *mlx, t_map *map)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		ft_freedom(map);
		exit(1);
	}
	mlx->window = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Fdf");
	if (!mlx->window)
	{
		free(mlx->mlx);
		ft_freedom(map);
		exit(1);
	}
	mlx->image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->image)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		free(mlx->mlx);
		ft_freedom(map);
		exit(1);
	}
	mlx->addr = mlx_get_data_addr(mlx->image, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
}

void	ft_initmlx(t_mlx *mlx, t_map *map)
{
	float	min;
	float	max;
	float	comp_x;
	float	comp_y;
	float	border;

	border = 200.0f;
	startmlx(mlx, map);
	map->linkmlx = mlx;
	mlx->zoom = 1.0f;
	ft_scaling(map);
	ft_minmax(map, 1, &min, &max);
	comp_y = max - min;
	if (comp_y < 1.0f)
		comp_y = 1.0f;
	ft_minmax(map, 2, &min, &max);
	comp_x = max - min;
	if (comp_x < 1.0f)
		comp_x = 1.0f;
	mlx->zoom = fminf((HEIGHT - border) / comp_y, (WIDTH - border) / comp_x);
	ft_minmax(map, 1, &min, &max);
	mlx->yoffset = (HEIGHT * 0.5f - (max - min) * 0.5f) - min;
	ft_minmax(map, 2, &min, &max);
	mlx->xoffset = (WIDTH * 0.5f - (max - min) * 0.5f) - min;
}

void	my_mlx_pixel_put(t_mlx *mlx, float fx, float fy, int color)
{
	int		x;
	int		y;
	char	*dst;

	x = (int)fx;
	y = (int)fy;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	if (mlx->endian == 0)
	{
		dst[0] = color & 0xFF;
		dst[1] = (color >> 8) & 0xFF;
		dst[2] = (color >> 16) & 0xFF;
		dst[3] = (color >> 24) & 0xFF;
	}
	else
	{
		dst[0] = (color >> 24) & 0xFF;
		dst[1] = (color >> 16) & 0xFF;
		dst[2] = (color >> 8) & 0xFF;
		dst[3] = color & 0xFF;
	}
}
