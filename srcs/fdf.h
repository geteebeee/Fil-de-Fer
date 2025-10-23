/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:18:13 by gorg              #+#    #+#             */
/*   Updated: 2025/01/04 00:33:09 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../Extras/mlx/mlx.h"
# include "../Extras/libft/srcs/libft.h"
# include "../Extras/gnl/get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define WIDTH 1200
# define HEIGHT 800
# define FLT_MAX 3.402823466e+38F
# define FLT_MIN 1.175494351e-38F

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_point
{
	int		z;
	t_color	color;
}	t_point;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*image;
	int		zoom;
	int		yoffset;
	int		xoffset;
	float	z_scale;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;
}	t_mlx;

typedef struct s_map
{
	t_point	**point;
	int		x;
	int		y;
	t_mlx	*linkmlx;
}	t_map;
typedef struct s_set
{
	int		x0;
	int		x1;
	int		y1;
	int		y0;
	int		dy;
	int		dx;
	int		y_dir;
	int		x_dir;
	t_color	start_color;
	t_color	end_color;
}	t_set;

t_map	*ft_mapping(int x, int y);
t_map	*ft_parsing(char *file);
t_map	*ft_free_split(t_map *map, char **split, char *line);
int		ft_width(char *line);
void	my_mlx_pixel_put(t_mlx *mlx, float fx, float fy, int color);
void	ft_initmlx(t_mlx *mlx, t_map *map);
float	ft_isox(int x, int y, float zoom);
float	ft_isoy(int x, int y, int z, t_mlx *mlx);
t_set	ft_points(int x, int y, int n, t_map *map);
void	ft_drawer(t_map *map);
t_color	ft_colorstep(t_color start, t_color end, int steps, int current_step);
void	ft_freedom(t_map *map);
void	ft_colorer(char *split, t_color *color);
int		ft_err_msg(char *msg);

#endif
