/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:04:20 by elee              #+#    #+#             */
/*   Updated: 2016/11/25 15:51:06 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define XSIZE 900
# define YSIZE 900
# define DEG 10
# define CC 15

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_ZOOMIN 24
# define KEY_ZOOMOUT 27

# define KEY_ROTX1 12
# define KEY_ROTX2 0
# define KEY_ROTY1 13
# define KEY_ROTY2 1
# define KEY_ROTZ1 14
# define KEY_ROTZ2 2

# define KEY_TOPR_PLUS 15
# define KEY_TOPG_PLUS 17
# define KEY_TOPB_PLUS 16
# define KEY_MIDR_PLUS 3
# define KEY_MIDG_PLUS 5
# define KEY_MIDB_PLUS 4
# define KEY_BOTR_PLUS 8
# define KEY_BOTG_PLUS 9
# define KEY_BOTB_PLUS 11

# define KEY_TOPR_MINUS 89
# define KEY_TOPG_MINUS 91
# define KEY_TOPB_MINUS 92
# define KEY_MIDR_MINUS 86
# define KEY_MIDG_MINUS 87
# define KEY_MIDB_MINUS 88
# define KEY_BOTR_MINUS 83
# define KEY_BOTG_MINUS 84
# define KEY_BOTB_MINUS 85

# define KEY_RESET 31

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
}				t_point;

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	t_point		**map;
	int			wcentx;
	int			wcenty;
	int			xmax;
	int			ymax;
	int			tranx;
	int			trany;
	int			rotx;
	int			roty;
	int			rotz;
	int			step;
	int			*color;
	int			top[3];
	int			mid[3];
	int			bot[3];
}				t_fdf;

void			handle_error(t_fdf *fdf, int file, int fd);
void			read_map_size(char *file, t_fdf *fdf);
void			read_map(char *file, t_fdf *fdf);

t_fdf			*fdf_init(int color[9]);
void			color_init(t_fdf *fdf);
void			fdf_reset(t_fdf *fdf);
int				key_func(int key, t_fdf *fdf);

void			zoom(t_fdf *fdf, t_point *point);
void			translate(t_fdf *fdf, t_point *point);
void			rotate(t_fdf *fdf, t_point *point);

t_point			**array_copy(t_fdf *fdf);
void			array_destroy(t_fdf *fdf, t_point **map);
void			array_iter(t_fdf *fdf, t_point **map, void f(t_fdf*, t_point*));
void			array_minmax(t_fdf *fdf, t_point **map, int minmax[2]);

void			draw_grid(t_fdf *fdf);

#endif
