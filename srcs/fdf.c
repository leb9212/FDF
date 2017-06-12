/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 15:51:45 by elee              #+#    #+#             */
/*   Updated: 2016/11/25 17:02:21 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"

t_fdf		*fdf_init(int color[9])
{
	t_fdf	*fdf;

	fdf = (t_fdf*)malloc(sizeof(t_fdf));
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, XSIZE, YSIZE, "fdf");
	fdf->map = NULL;
	fdf->wcentx = XSIZE / 2;
	fdf->wcenty = YSIZE / 2;
	fdf->xmax = 0;
	fdf->ymax = 0;
	fdf->tranx = 0;
	fdf->trany = 0;
	fdf->rotx = 0;
	fdf->roty = 0;
	fdf->rotz = 0;
	fdf->step = 1;
	fdf->color = color;
	return (fdf);
}

void		color_init(t_fdf *fdf)
{
	if (fdf->color[0] == -1)
	{
		fdf->top[0] = 255;
		fdf->top[1] = 255;
		fdf->top[2] = 51;
		fdf->mid[0] = 51;
		fdf->mid[1] = 255;
		fdf->mid[2] = 255;
		fdf->bot[0] = 51;
		fdf->bot[1] = 255;
		fdf->bot[2] = 51;
	}
	else
	{
		fdf->top[0] = fdf->color[0];
		fdf->top[1] = fdf->color[1];
		fdf->top[2] = fdf->color[2];
		fdf->mid[0] = fdf->color[3];
		fdf->mid[1] = fdf->color[4];
		fdf->mid[2] = fdf->color[5];
		fdf->bot[0] = fdf->color[6];
		fdf->bot[1] = fdf->color[7];
		fdf->bot[2] = fdf->color[8];
	}
}

static void	color_func(int key, t_fdf *fdf)
{
	fdf->top[0] += (fdf->top[0] <= 255 - CC && key == KEY_TOPR_PLUS) ? CC : 0;
	fdf->top[1] += (fdf->top[1] <= 255 - CC && key == KEY_TOPG_PLUS) ? CC : 0;
	fdf->top[2] += (fdf->top[2] <= 255 - CC && key == KEY_TOPB_PLUS) ? CC : 0;
	fdf->mid[0] += (fdf->mid[0] <= 255 - CC && key == KEY_MIDR_PLUS) ? CC : 0;
	fdf->mid[1] += (fdf->mid[1] <= 255 - CC && key == KEY_MIDG_PLUS) ? CC : 0;
	fdf->mid[2] += (fdf->mid[2] <= 255 - CC && key == KEY_MIDB_PLUS) ? CC : 0;
	fdf->bot[0] += (fdf->bot[0] <= 255 - CC && key == KEY_BOTR_PLUS) ? CC : 0;
	fdf->bot[1] += (fdf->bot[1] <= 255 - CC && key == KEY_BOTG_PLUS) ? CC : 0;
	fdf->bot[2] += (fdf->bot[2] <= 255 - CC && key == KEY_BOTB_PLUS) ? CC : 0;
	fdf->top[0] -= (fdf->top[0] >= CC && key == KEY_TOPR_MINUS) ? CC : 0;
	fdf->top[1] -= (fdf->top[1] >= CC && key == KEY_TOPG_MINUS) ? CC : 0;
	fdf->top[2] -= (fdf->top[2] >= CC && key == KEY_TOPB_MINUS) ? CC : 0;
	fdf->mid[0] -= (fdf->mid[0] >= CC && key == KEY_MIDR_MINUS) ? CC : 0;
	fdf->mid[1] -= (fdf->mid[1] >= CC && key == KEY_MIDG_MINUS) ? CC : 0;
	fdf->mid[2] -= (fdf->mid[2] >= CC && key == KEY_MIDB_MINUS) ? CC : 0;
	fdf->bot[0] -= (fdf->bot[0] >= CC && key == KEY_BOTR_MINUS) ? CC : 0;
	fdf->bot[1] -= (fdf->bot[1] >= CC && key == KEY_BOTG_MINUS) ? CC : 0;
	fdf->bot[2] -= (fdf->bot[2] >= CC && key == KEY_BOTB_MINUS) ? CC : 0;
}

void		fdf_reset(t_fdf *fdf)
{
	fdf->tranx = 0;
	fdf->trany = 0;
	fdf->rotx = 0;
	fdf->roty = 0;
	fdf->rotz = 0;
	fdf->step = MIN(XSIZE * 0.75 / fdf->xmax, YSIZE * 0.75 / fdf->ymax);
	fdf->step += (fdf->step == 0) ? 1 : 0;
	color_init(fdf);
}

int			key_func(int key, t_fdf *fdf)
{
	color_func(key, fdf);
	(key == KEY_ESC) ? handle_error(fdf, 0, 0) : 0;
	fdf->tranx -= (key == KEY_LEFT) ? 1 : 0;
	fdf->tranx += (key == KEY_RIGHT) ? 1 : 0;
	fdf->trany -= (key == KEY_UP) ? 1 : 0;
	fdf->trany += (key == KEY_DOWN) ? 1 : 0;
	fdf->rotx += (key == KEY_ROTX1) ? 1 : 0;
	fdf->rotx -= (key == KEY_ROTX2) ? 1 : 0;
	fdf->roty += (key == KEY_ROTY1) ? 1 : 0;
	fdf->roty -= (key == KEY_ROTY2) ? 1 : 0;
	fdf->rotz += (key == KEY_ROTZ1) ? 1 : 0;
	fdf->rotz -= (key == KEY_ROTZ2) ? 1 : 0;
	fdf->step += (key == KEY_ZOOMIN) ? 1 : 0;
	fdf->step -= (fdf->step != 1 && key == KEY_ZOOMOUT) ? 1 : 0;
	(key == KEY_RESET) ? fdf_reset(fdf) : 0;
	draw_grid(fdf);
	return (0);
}
