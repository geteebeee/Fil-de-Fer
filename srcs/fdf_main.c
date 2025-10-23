/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:41:00 by gorg              #+#    #+#             */
/*   Updated: 2024/11/14 19:18:33 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	close_window(t_map *map)
{
	mlx_destroy_image(map->linkmlx->mlx, map->linkmlx->image);
	mlx_destroy_window(map->linkmlx->mlx, map->linkmlx->window);
	mlx_destroy_display(map->linkmlx->mlx);
	free(map->linkmlx->mlx);
	free(map->linkmlx);
	ft_freedom(map);
	exit (0);
}

static int	on_keypress(int keysym, t_map *map)
{
	if (keysym == XK_Escape)
		close_window(map);
	return (0);
}

static int	extension(char *filename)
{
	int		ext_len;
	int		file_len;
	char	*ext;

	ext = ".fdf";
	ext_len = ft_strlen(ext);
	file_len = ft_strlen(filename);
	return (ft_strncmp(filename + file_len - ext_len, ext, 4));
}

static int	is_dir(const char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	*mlx;

	if (argc != 2 || extension(argv[1]) != 0 || is_dir(argv[1]) == 1)
		return (ft_err_msg("Usage: ./fdf <filename>"));
	map = ft_parsing(argv[1]);
	if (!map)
		return (1);
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
	{
		ft_freedom(map);
		return (1);
	}
	ft_initmlx(mlx, map);
	ft_drawer(map);
	mlx_hook(mlx->window, KeyRelease, KeyReleaseMask, &on_keypress, map);
	mlx_hook(mlx->window, DestroyNotify,
		StructureNotifyMask, close_window, map);
	mlx_loop(mlx->mlx);
	return (0);
}
