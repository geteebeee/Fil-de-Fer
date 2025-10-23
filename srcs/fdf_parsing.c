/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:07:49 by gorg              #+#    #+#             */
/*   Updated: 2024/11/14 18:38:05 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_fill_line(t_map *map, char *line, int y)
{
	char	*trim;
	char	**split;
	int		x;

	trim = ft_strtrim(line, " \n\t\r");
	if (!trim)
		return (0);
	split = ft_split(trim, ' ');
	free(trim);
	if (!split)
		return (0);
	x = 0;
	while (x < map->x)
	{
		map->point[y][x].z = ft_atoi(split[x]);
		ft_colorer(split[x], &map->point[y][x].color);
		free(split[x]);
		x++;
	}
	free(split);
	return (1);
}

static t_map	*ft_fillingloop(int fd, t_map *map, int *x, int *y)
{
	char	*line;

	*y = 0;
	line = get_next_line(fd);
	while (line != NULL && *y < map->y)
	{
		if (!ft_fill_line(map, line, *y))
		{
			free(line);
			return (ft_free_split(map, NULL, NULL));
		}
		free(line);
		(*y)++;
		line = get_next_line(fd);
	}
	*x = map->x;
	return (map);
}

static t_map	*ft_filling(t_map *map, char *file)
{
	int	fd;
	int	y;
	int	x;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_err_msg("Error opening file");
		return (NULL);
	}
	ft_fillingloop(fd, map, &x, &y);
	if (!map)
		return (NULL);
	close (fd);
	return (map);
}

static void	*ft_parsingloop(int fd, int *width, int *height)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line != NULL)
	{
		trimmed = ft_strtrim(line, " \n\t\r");
		free(line);
		if (!trimmed)
			return (NULL);
		if (*height == 0)
			*width = ft_width(trimmed);
		else if (ft_width(trimmed) != *width)
		{
			free(trimmed);
			return (NULL);
		}
		(*height)++;
		free(trimmed);
		line = get_next_line(fd);
	}
	free(line);
	return ((void *)1);
}

t_map	*ft_parsing(char *file)
{
	t_map	*map;
	int		height;
	int		width;
	int		fd;

	map = NULL;
	height = 0;
	width = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_err_msg("Error opening file");
		return (NULL);
	}
	if (!ft_parsingloop(fd, &width, &height))
	{
		close(fd);
		ft_err_msg("Error: invalid map");
		return (NULL);
	}
	close(fd);
	map = ft_mapping(width, height);
	if (!map)
		return (NULL);
	return (ft_filling(map, file));
}
