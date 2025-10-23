/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:55:40 by gorg              #+#    #+#             */
/*   Updated: 2024/11/14 19:19:31 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*ft_free_split(t_map *map, char **split, char *line)
{
	int	i;

	ft_putendl_fd("Error: Split failed", 2);
	if (split)
	{
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
	}
	if (line)
		free(line);
	if (map)
		ft_freedom(map);
	return (0);
}

int	ft_err_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (0);
}

void	ft_colorer(char *split, t_color *color)
{
	char	*ptr;
	int		convert;

	if (!split)
	{
		color->r = 255;
		color->g = 255;
		color->b = 255;
		return ;
	}
	ptr = ft_strrchr(split, ',');
	if (ptr != 0)
	{
		ptr++;
		convert = ft_atoi_base(ptr, 16);
		color->r = (convert >> 16) & 0xFF;
		color->g = (convert >> 8) & 0xFF;
		color->b = convert & 0xFF;
	}
	else
	{
		color->r = 255;
		color->g = 255;
		color->b = 255;
	}
}

int	ft_width(char *line)
{
	int		width;
	int		i;
	char	**split;

	width = 0;
	i = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	while (split[width])
		width++;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (width);
}

t_map	*ft_mapping(int x, int y)
{
	t_map	*map;
	int		i;

	i = -1;
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->x = x;
	map->y = y;
	map->point = malloc(sizeof(t_point *) * y);
	if (!map->point)
	{
		free(map);
		return (NULL);
	}
	while (++i < y)
	{
		map->point[i] = malloc(sizeof(t_point) * x);
		if (!map->point[i])
		{
			ft_freedom(map);
			return (NULL);
		}
	}
	return (map);
}
