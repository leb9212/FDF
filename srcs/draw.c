/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 12:30:43 by elee              #+#    #+#             */
/*   Updated: 2016/11/24 21:11:50 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"

static void	make_color(t_fdf *fdf, int color[3])
{
	color[0] = ((fdf->top[0]) << 16) + ((fdf->top[1]) << 8) + (fdf->top[2]);
	color[1] = ((fdf->mid[0]) << 16) + ((fdf->mid[1]) << 8) + (fdf->mid[2]);
	color[2] = ((fdf->bot[0]) << 16) + ((fdf->bot[1]) << 8) + (fdf->bot[2]);
}

static int	color_grad(t_fdf *fdf, double z, int minmax[2])
{
	double	per;
	int		rgb[3];
	int		color[3];
	int		c[2];
	int		ret_c;

	rgb[0] = 0xFF0000;
	rgb[1] = 0x00FF00;
	rgb[2] = 0x0000FF;
	make_color(fdf, color);
	c[0] = color[1];
	ret_c = color[1];
	if (z != 0.0)
	{
		per = (z < 0.0) ? z / minmax[0] : z / minmax[1];
		c[1] = (z < 0.0) ? color[2] : color[0];
		ret_c = (int)(((int)((c[1] & rgb[0]) * per) & rgb[0])
			+ ((int)((c[0] & rgb[0]) * (1 - per)) & rgb[0]) |
			(int)((int)((c[1] & rgb[1]) * per) & rgb[1])
			+ ((int)((c[0] & rgb[1]) * (1 - per)) & rgb[1]) |
			(int)((int)((c[1] & rgb[2]) * per) & rgb[2])
			+ ((int)((c[0] & rgb[2]) * (1 - per)) & rgb[2]));
	}
	return (ret_c);
}

static int	stop_condition(t_point a, t_point b)
{
	if ((a.x < 0 && b.x < 0) || (a.y < 0 && b.y < 0) ||
			(a.x > XSIZE && b.x > XSIZE) || (a.y > YSIZE && b.y > YSIZE))
		return (1);
	return (0);
}

static void	draw_line(t_fdf *fdf, t_point a, t_point b, int minmax[2])
{
	int		d_pt[7];

	if (stop_condition(a, b))
		return ;
	d_pt[0] = ABS(b.x - a.x);
	d_pt[1] = ABS(b.y - a.y);
	d_pt[2] = SIGN(b.x - a.x);
	d_pt[3] = SIGN(b.y - a.y);
	d_pt[5] = 0;
	if (d_pt[1] > d_pt[0] && (d_pt[5] = 1))
		SWAP(d_pt[1], d_pt[0]);
	d_pt[4] = 2 * d_pt[1] - d_pt[0];
	d_pt[6] = -1;
	while (++d_pt[6] < d_pt[0])
	{
		mlx_pixel_put(fdf->mlx, fdf->win, a.x, a.y,
		color_grad(fdf, a.z + (double)(b.z - a.z) * d_pt[6] / d_pt[0], minmax));
		while (d_pt[4] >= 0)
		{
			d_pt[4] -= 2 * d_pt[0];
			(d_pt[5]) ? (a.x += d_pt[2]) : (a.y += d_pt[3]);
		}
		d_pt[4] += 2 * d_pt[1];
		(d_pt[5]) ? (a.y += d_pt[3]) : (a.x += d_pt[2]);
	}
}

void		draw_grid(t_fdf *fdf)
{
	int		i;
	int		j;
	int		minmax[2];
	t_point	**map;

	map = array_copy(fdf);
	mlx_clear_window(fdf->mlx, fdf->win);
	array_iter(fdf, map, &zoom);
	array_iter(fdf, map, &rotate);
	array_iter(fdf, map, &translate);
	array_minmax(fdf, map, minmax);
	j = -1;
	while (++j < fdf->ymax)
	{
		i = -1;
		while (++i < fdf->xmax)
		{
			if (j < fdf->ymax - 1)
				draw_line(fdf, map[j][i], map[j + 1][i], minmax);
			if (i < fdf->xmax - 1)
				draw_line(fdf, map[j][i], map[j][i + 1], minmax);
		}
	}
	array_destroy(fdf, map);
}
